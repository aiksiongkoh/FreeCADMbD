/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <cmath>
#include <numbers>

#include "OrbitAngleZIecJec.h"
#include "Numeric.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<OrbitAngleZIecJec> OrbitAngleZIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OrbitAngleZIecJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OrbitAngleZIecJec::initialize()
{
    KinematicIJ::initialize();
    init_xyIeJeIe();
}

void OrbitAngleZIecJec::calcPostDynCorrectorIteration()
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

void OrbitAngleZIecJec::init_xyIeJeIe()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void OrbitAngleZIecJec::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void OrbitAngleZIecJec::initializeLocally()
{
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void OrbitAngleZIecJec::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    if (thez == std::numeric_limits<double>::min()) {
        auto x = xIeJeIe->value();
        auto y = yIeJeIe->value();
        if (x > 0.0) {
            thez = std::atan2(y, x);
        }
        else {
            thez = Numeric::arcTan0to2piYoverX(y, x);
        }
    }
    KinematicIJ::postInput();
}

void OrbitAngleZIecJec::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    KinematicIJ::postPosICIteration();
}

void OrbitAngleZIecJec::preAccIC()
{
    if (thez == std::numeric_limits<double>::min()) prePosIC();
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    KinematicIJ::preAccIC();
}

void OrbitAngleZIecJec::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    assert(thez != std::numeric_limits<double>::min());
    KinematicIJ::prePosIC();
}

void OrbitAngleZIecJec::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    KinematicIJ::preVelIC();
}

void OrbitAngleZIecJec::simUpdateAll()
{
    xIeJeIe->simUpdateAll();
    yIeJeIe->simUpdateAll();
    KinematicIJ::simUpdateAll();
}

double OrbitAngleZIecJec::value()
{
    return thez;
}

void OrbitAngleZIecJec::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    yIeJeIe->postDynPredictor();
    KinematicIJ::postDynPredictor();
}

void OrbitAngleZIecJec::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    yIeJeIe->postDynCorrectorIteration();
    KinematicIJ::postDynCorrectorIteration();
}

void OrbitAngleZIecJec::preDynOutput()
{
    xIeJeIe->preDynOutput();
    yIeJeIe->preDynOutput();
    KinematicIJ::preDynOutput();
}

void OrbitAngleZIecJec::postDynOutput()
{
    xIeJeIe->postDynOutput();
    yIeJeIe->postDynOutput();
    KinematicIJ::postDynOutput();
}
