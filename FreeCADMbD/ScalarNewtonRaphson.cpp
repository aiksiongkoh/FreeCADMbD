/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ScalarNewtonRaphson.h"
#include "SystemSolver.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ScalarNewtonRaphson> ScalarNewtonRaphson::With()
{
    auto inst = std::make_shared<ScalarNewtonRaphson>();
    inst->initialize();
    return inst;
}

void ScalarNewtonRaphson::initializeGlobally()
{
    throw SimulationStoppingError("To be implemented.");
    //x = system->x;
}

void ScalarNewtonRaphson::fillY()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScalarNewtonRaphson::fillPyPx()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScalarNewtonRaphson::calcyNorm()
{
    yNorm = 0.5 * y * y;
}

void ScalarNewtonRaphson::solveEquations()
{
    dx = -y / pypx;
}

void ScalarNewtonRaphson::updatexold()
{
    xold = x;
}

void ScalarNewtonRaphson::calcdxNorm()
{
    dxNorm = std::abs(dx);
}

void ScalarNewtonRaphson::xEqualxoldPlusdx()
{
    x = xold + dx;
}

void ScalarNewtonRaphson::passRootToSystem()
{
    throw SimulationStoppingError("To be implemented.");
}
