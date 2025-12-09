/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <fstream>    
#include <iomanip>

#include "SystemNewtonRaphson.h"
#include "SystemSolver.h"
#include "SparseMatrix.h"
#include "MatrixSolver.h"
#include "GESpMatParPvMarkoFast.h"
#include "GESpMatParPvPrecise.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<SystemNewtonRaphson> SystemNewtonRaphson::With()
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<SystemNewtonRaphson>();
}

void SystemNewtonRaphson::initializeGlobally()
{
    assignEquationNumbers();
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->useEquationNumbers(); });
    createVectorsAndMatrices();
    matrixSolver = matrixSolverClassNew();
}

void SystemNewtonRaphson::assignEquationNumbers()
{
	throw SimulationStoppingError("To be implemented.");
}

void SystemNewtonRaphson::createVectorsAndMatrices()
{
    x = std::make_shared<FullColumn<double>>(n);
    y = std::make_shared<FullColumn<double>>(n);
    pypx = std::make_shared <SparseMatrix<double>>(n, n);
}

std::shared_ptr<MatrixSolver> SystemNewtonRaphson::matrixSolverClassNew()
{
    return GESpMatParPvMarkoFast::With();
}

void SystemNewtonRaphson::calcdxNorm()
{
    VectorNewtonRaphson::calcdxNorm();
    std::stringstream ss;
    ss << std::setprecision(std::numeric_limits<double>::max_digits10);
    ss << "MbD: Convergence = " << dxNorm;
    auto str = ss.str();
    system->logString(str);
}

void SystemNewtonRaphson::basicSolveEquations()
{
	auto debug = false;
	if (debug) {
		outputSpreadsheet();
	}
	dx = matrixSolver->solvewithsaveOriginal(pypx, y->negated(), false);
}

void SystemNewtonRaphson::handleSingularMatrix()
{
    auto& r = *matrixSolver;
    std::string str = typeid(r).name();
    if (str.find("GESpMatParPvMarkoFast") != std::string::npos) {
        matrixSolver = GESpMatParPvPrecise::With();
        solveEquations();
    }
    else {
        str = typeid(r).name();
        if (str.find("GESpMatParPvPrecise") != std::string::npos) {
            str = "MbD: Singular Matrix Error. ";
            system->logString(str);
            matrixSolver->throwSingularMatrixError("SystemNewtonRaphson");
        }
        else {
            throw SimulationStoppingError("To be implemented.");
        }
    }
}

void SystemNewtonRaphson::outputSpreadsheet()
{
    std::ofstream os("../../testapp/spreadsheetcpp.csv");
    os << std::setprecision(std::numeric_limits<double>::max_digits10);
    for (size_t i = 0; i < pypx->nrow(); i++)
    {
        auto rowi = pypx->at(i);
        for (size_t j = 0; j < pypx->ncol(); j++)
        {
        	if (j > 0) os << '\t';
            if (rowi->find(j) == rowi->end()) {
                os << 0.0;
            }
            else {
                os << rowi->at(j);
            }
            os << '\t';
        }
        os << "\t\t" << y->at(i) << std::endl;
    }
}
