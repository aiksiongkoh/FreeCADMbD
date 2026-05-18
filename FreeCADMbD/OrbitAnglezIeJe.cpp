/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>
#include <numbers>

#include "OrbitAngleZIeJe.h"
#include "Numeric.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void OrbitAngleZIeJe::postStaticIteration()
{
    xIeJeIe->postStaticIteration();
    yIeJeIe->postStaticIteration();
    KinematicIeJe::postStaticIteration();
}

void OrbitAngleZIeJe::preStatic()
{
    xIeJeIe->preStatic();
    yIeJeIe->preStatic();
    KinematicIeJe::preStatic();
}

std::shared_ptr<OrbitAngleZIeJe> OrbitAngleZIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    auto inst = std::make_shared<OrbitAngleZIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OrbitAngleZIeJe::initialize()
{
    KinematicIeJe::initialize();
    init_xyIeJeIe();
}

void OrbitAngleZIeJe::simUpdateAll()
{
    auto x = xIeJeIe->value();
    auto y = yIeJeIe->value();
    auto sumOfSquares = x * x + (y * y);
    auto diffOfSquares = y * y - (x * x);
    auto sumOfSquaresSquared = sumOfSquares * sumOfSquares;
    auto thez0to2pi = Numeric::arcTan0to2piYoverX(y, x);
    thez = std::round((thez - thez0to2pi) / (2.0 * std::numbers::pi)) * (2.0 * std::numbers::pi) + thez0to2pi;
    cosOverSSq = x / sumOfSquares;
    sinOverSSq = y / sumOfSquares;
    twoCosSinOverSSqSq = 2.0 * x * y / sumOfSquaresSquared;
    dSqOverSSqSq = diffOfSquares / sumOfSquaresSquared;
}

void OrbitAngleZIeJe::init_xyIeJeIe()
{
    // Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void OrbitAngleZIeJe::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void OrbitAngleZIeJe::initializeLocally()
{
    KinematicIeJe::initializeLocally();
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void OrbitAngleZIeJe::useUniqueDispIeJeO()
{
    xIeJeIe->useUniqueDispIeJeO();
    yIeJeIe->useUniqueDispIeJeO();
}

void OrbitAngleZIeJe::useUniqueDispIeJeKe()
{
    xIeJeIe->useUniqueDispIeJeKe();
    yIeJeIe->useUniqueDispIeJeKe();
}

void OrbitAngleZIeJe::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    if (thez == std::numeric_limits<double>::min())
    {
        auto x = xIeJeIe->value();
        auto y = yIeJeIe->value();
        if (x > 0.0)
        {
            thez = std::atan2(y, x);
        }
        else
        {
            thez = Numeric::arcTan0to2piYoverX(y, x);
        }
    }
    KinematicIeJe::postInput();
}

void OrbitAngleZIeJe::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    KinematicIeJe::postPosICIteration();
}

void OrbitAngleZIeJe::preAccIC()
{
    if (thez == std::numeric_limits<double>::min())
        prePosIC();
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    KinematicIeJe::preAccIC();
}

void OrbitAngleZIeJe::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    assert(thez != std::numeric_limits<double>::min());
    KinematicIeJe::prePosIC();
}

void OrbitAngleZIeJe::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    KinematicIeJe::preVelIC();
}

double OrbitAngleZIeJe::value()
{
    return thez;
}

void OrbitAngleZIeJe::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    yIeJeIe->postDynPredictor();
    KinematicIeJe::postDynPredictor();
}

void OrbitAngleZIeJe::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    yIeJeIe->postDynCorrectorIteration();
    KinematicIeJe::postDynCorrectorIteration();
}

void OrbitAngleZIeJe::preDynOutput()
{
    xIeJeIe->preDynOutput();
    yIeJeIe->preDynOutput();
    KinematicIeJe::preDynOutput();
}

void OrbitAngleZIeJe::postDynOutput()
{
    xIeJeIe->postDynOutput();
    yIeJeIe->postDynOutput();
    KinematicIeJe::postDynOutput();
}
