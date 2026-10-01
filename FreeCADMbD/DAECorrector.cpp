/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <fstream>    

#include "DAECorrector.h"
#include "BasicDAEIntegrator.h"
#include "GESpMatParPvMarkoFast.h"
#include "GESpMatParPvPrecise.h"
#include "SystemSolver.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DAECorrector> DAECorrector::With()
{
    auto inst = std::make_shared<DAECorrector>();
    inst->initialize();
    return inst;
}

void DAECorrector::iterate()
{
    //VectorNewtonRaphson::iterate();    //Inlined to help debugging
    iterNo = SIZE_MAX;
    fillY();
    calcyNorm();
    yNorms->push_back(yNorm);

    while (true) {
        incrementIterNo();
        fillPyPx();
        //outputSpreadsheet();
        solveEquations();
        calcDXNormImproveRootCalcYNorm();
        if (isConverged()) {
            //std::cout << "iterNo = " << iterNo << std::endl;
            break;
        }
    }
}

void DAECorrector::fillPyPx()
{
    pypx = daeSystem->calcG();
}

void DAECorrector::fillY()
{
    y = daeSystem->fillF();
}

void DAECorrector::passRootToSystem()
{
    daeSystem->y = x;
}

void DAECorrector::calcdxNorm()
{
    dxNorm = daeSystem->corErrorNormFromwrt(dx, x);
    std::stringstream ss;
    ss << std::setprecision(std::numeric_limits<double>::max_digits10);
    ss << "          ";
    ss << "MbD: Convergence = " << dxNorm;
    auto str = ss.str();
    daeSystem->logString(str);
}

void DAECorrector::basicSolveEquations()
{
    dx = matrixSolver->solvewithsaveOriginal(pypx, y->negated(), false);
}

void DAECorrector::solveEquations()
{
    try {
        basicSolveEquations();
    }
    catch (const SingularMatrixError& ex) {
        handleSingularMatrix();
    }
}

std::shared_ptr<MatrixSolver> DAECorrector::matrixSolverClassNew()
{
    return GESpMatParPvMarkoFast::With();
}

void DAECorrector::handleSingularMatrix()
{
    const auto solverName = std::string(typeid(*matrixSolver).name());
    if (solverName.find("GESpMatParPvMarkoFast") != std::string::npos) {
        matrixSolver = GESpMatParPvPrecise::With();
        solveEquations();
        return;
    }

    if (solverName.find("GESpMatParPvPrecise") != std::string::npos) {
        matrixSolver->throwSingularMatrixError("DAECorrector::handleSingularMatrix");
    }

    throw SimulationStoppingError("Unhandled matrix solver in DAECorrector::handleSingularMatrix.");
}

void DAECorrector::initializeGlobally()
{
    iterMax = daeSystem->iterMax();
    x = daeSystem->y;
    matrixSolver = matrixSolverClassNew();
}

void DAECorrector::run()
{
    preRun();
    initializeLocally();
    initializeGlobally();
    iterate();
    finalize();
    reportStats();
    postRun();
}

void DAECorrector::preRun()
{
    //auto basicDAEIntegrator = static_cast<BasicDAEIntegrator*>(system);
    daeSystem->preDAECorrector();
}

void DAECorrector::askSystemToUpdate()
{
    daeSystem->updateForDAECorrector();
}

bool DAECorrector::isConverged()
{
    if (daeSystem->isConvergedForand(iterNo, dxNorms)) return true;
    if (iterNo == 0 || !std::isfinite(dxNorm) || dxNorm < 0.5 * dxNorms->at(iterNo - 1)) return false;

    // A BDF Jacobian contains coefficients proportional to 1/h. At small
    // steps, position roundoff can therefore produce momentum corrections
    // above the requested tolerance. Reducing h makes this worse. Once the
    // corrections stall, also allow convergence at the numerical limit, but
    // only if EVERY residual has a small componentwise backward error:
    // |F_i| <= 8 epsilon sum_j |J_ij| max(|x_j|, absoluteTolerance_j).
    // Refresh J at the corrected state; do not use a factored/scaled matrix.
    fillPyPx();
    for (size_t i = 0; i < y->size(); ++i) {
        double scale = 0.0;
        for (const auto& entry : *pypx->at(i)) {
            scale += std::abs(entry.second) * std::max(std::abs(x->at(entry.first)), daeSystem->corAbsTol->at(entry.first));
        }
        if (!std::isfinite(scale) || !(std::abs(y->at(i)) <= 8.0 * std::numeric_limits<double>::epsilon() * scale)) return false;
    }
    return true;
}

void DAECorrector::postRun()
{
    daeSystem->postDAECorrector();
}

void DAECorrector::setSystem(Solver* sys)
{
    daeSystem = static_cast<BasicDAEIntegrator*>(sys);
}

void DAECorrector::reportStats()
{
    statistics->iterNo = iterNo;
    daeSystem->useDAECorrectorStats(statistics);
}

void DAECorrector::outputSpreadsheet()
{
    std::ofstream os("../testapp/spreadsheetcpp.csv");
    os << std::setprecision(std::numeric_limits<double>::max_digits10);
    for (size_t i = 0; i < pypx->nrow(); i++)
    {
        auto rowi = pypx->at(i);
        for (size_t j = 0; j < pypx->ncol(); j++)
        {
            if (rowi->find(j) == rowi->end()) {
                os << 0.0;
            }
            else {
                os << rowi->at(j);
            }
            os << '\t';
        }
        os << "\t" << y->at(i) << std::endl;
    }
}
