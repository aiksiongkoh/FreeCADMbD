/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <memory>
#include <cassert>
#include <fstream>    

#include "VectorNewtonRaphson.h"
#include "MatrixSolver.h"
#include "GEFullMatParPv.h"
#include "SystemSolver.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VectorNewtonRaphson> VectorNewtonRaphson::With()
{
    throw SimulationStoppingError("To be implemented by concrete subclasses.");
}

void VectorNewtonRaphson::initializeGlobally()
{
    throw SimulationStoppingError("To be implemented.");
    //system->fillVarVector(x);
}

void VectorNewtonRaphson::run()
{
    preRun();
    initializeLocally();
    initializeGlobally();
    iterate();
    postRun();
}

std::shared_ptr<MatrixSolver> VectorNewtonRaphson::matrixSolverClassNew()
{
    return GEFullMatParPv::With();
}

void VectorNewtonRaphson::fillY()
{
    throw SimulationStoppingError("To be implemented.");
}

void VectorNewtonRaphson::calcyNorm()
{
    yNorm = 0.5 * y->sumOfSquares();
}

void VectorNewtonRaphson::solveEquations()
{
    try {
        basicSolveEquations();
    }
    catch (const SingularMatrixError& ex) {
        handleSingularMatrix();
    }
}

void VectorNewtonRaphson::updatexold()
{
    xold = x;
}

void VectorNewtonRaphson::calcdxNorm()
{
    dxNorm = dx->rootMeanSquare();
}

bool VectorNewtonRaphson::isConverged()
{
    return dxNorms->at(iterNo) < dxTol || isConvergedToNumericalLimit();
}

void VectorNewtonRaphson::xEqualxoldPlusdx()
{
    x = xold->plusFullColumn(dx);
}

void VectorNewtonRaphson::basicSolveEquations()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void VectorNewtonRaphson::handleSingularMatrix()
{
    throw SimulationStoppingError("To be implemented.");
}
