/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <assert.h>
#include <exception>

#include "PosICNewtonRaphson.h"
#include "SingularMatrixError.h"
#include "SystemSolver.h"
#include "Part.h"
#include "Constraint.h"
#include "GESpMatParPvPrecise.h"
#include "GESpMatFullPvPosIC.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<PosICNewtonRaphson> PosICNewtonRaphson::With()
{
    auto inst = std::make_shared<PosICNewtonRaphson>();
    inst->initialize();
    return inst;
}

void PosICNewtonRaphson::run()
{
    while (true) {
        try {
            //VectorNewtonRaphson::run();   //Inlined to help debugging
            preRun();
            initializeLocally();
            initializeGlobally();
            iterate();
            postRun();
            break;
        }
        catch (SingularMatrixError ex) {
            auto redundantEqnNos = ex.getRedundantEqnNos();
            system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->removeRedundantConstraints(redundantEqnNos); });
            system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->constraintsReport(); });
            system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->setqsu(qsuOld); });
        }
    }
}

void PosICNewtonRaphson::iterate()
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

void PosICNewtonRaphson::preRun()
{
    std::string str("MbD: Assembling system. ");
    system->logString(str);
    PosNewtonRaphson::preRun();
}

void PosICNewtonRaphson::assignEquationNumbers()
{
    auto parts = system->parts();
    //auto contactEndFrames = system->contactEndFrames();
    //auto uHolders = system->uHolders();
    auto essentialConstraints = system->essentialConstraints();
    auto displacementConstraints = system->displacementConstraints();
    auto perpendicularConstraints = system->perpendicularConstraints();
    size_t eqnNo = 0;
    for (auto& part : *parts) {
        part->iqX(eqnNo);
        eqnNo = eqnNo + 3;
        part->iqE(eqnNo);
        eqnNo = eqnNo + 4;
    }
    //for (auto& endFrm : *contactEndFrames) {
    //    endFrm->is(eqnNo);
    //    eqnNo = eqnNo + endFrm->sSize();
    //}
    //for (auto& uHolder : *uHolders) {
    //    uHolder->iu(eqnNo);
    //    eqnNo += 1;
    //}
    auto nEqns = eqnNo;    //C++ uses index 0.
    nqsu = nEqns;
    for (auto& con : *essentialConstraints) {
        con->iG = eqnNo;
        eqnNo += 1;
    }
    auto lastEssenConEqnNo = eqnNo - 1;
    for (auto& con : *displacementConstraints) {
        con->iG = eqnNo;
        eqnNo += 1;
    }
    auto lastDispConEqnNo = eqnNo - 1;
    for (auto& con : *perpendicularConstraints) {
        con->iG = eqnNo;
        eqnNo += 1;
    }
    auto lastEqnNo = eqnNo - 1;
    nEqns = eqnNo;    //C++ uses index 0.
    n = nEqns;
    auto rangelimits = { lastEssenConEqnNo + 1, lastDispConEqnNo + 1, lastEqnNo + 1 };
    pivotRowLimits = std::make_shared<std::vector<size_t>>(rangelimits);
}

bool PosICNewtonRaphson::isConverged()
{
    return isConvergedToNumericalLimit();
}

void PosICNewtonRaphson::handleSingularMatrix()
{
    nSingularMatrixError++;
    if (nSingularMatrixError == 1) {
        lookForRedundantConstraints();
        matrixSolver = matrixSolverClassNew();
    }
    else {
        auto& r = *matrixSolver;
        std::string str = typeid(r).name();
        if (str.find("GESpMatParPvMarkoFast") != std::string::npos) {
            matrixSolver = GESpMatParPvPrecise::With();
            solveEquations();
        }
        else {
            auto& msRef = *matrixSolver.get(); // extrapolated to suppress warning
            str = typeid(msRef).name();
            (void) msRef;                      // also for warning suppression
            if (str.find("GESpMatParPvPrecise") != std::string::npos) {
                lookForRedundantConstraints();
                matrixSolver = matrixSolverClassNew();
            } else {
                throw SimulationStoppingError("To be implemented.");
            }
        }
    }
}

void PosICNewtonRaphson::lookForRedundantConstraints()
{
    std::string str("MbD: Checking for redundant constraints.");
    system->logString(str);
    auto posICsolver = GESpMatFullPvPosIC::With();
    posICsolver->system = this;
    dx = posICsolver->solvewithsaveOriginal(pypx, y->negated(), false);
}
