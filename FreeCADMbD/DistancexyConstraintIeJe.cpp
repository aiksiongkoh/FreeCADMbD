/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIeJe.h"
#include "DistancexyConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIeJe> DistancexyConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<DistancexyConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    init_xyIeJeIe();
}

void DistancexyConstraintIeJe::simUpdateAll()
{
    //aG = xIeJeIe^2 + yIeJeIe^2 - C^2;
    auto x = xIeJeIe->value();
    auto y = yIeJeIe->value();
    aG = x * x + (y * y) - (aConstant * aConstant);
}

void DistancexyConstraintIeJe::init_xyIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistancexyConstraintIeJe::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void DistancexyConstraintIeJe::initializeLocally()
{
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void DistancexyConstraintIeJe::useUniqueDispIeJeO()
{
    ConstraintIeJe::useUniqueDispIeJeO();
    xIeJeIe->useUniqueDispIeJeO();
    yIeJeIe->useUniqueDispIeJeO();
}

void DistancexyConstraintIeJe::useUniqueDispIeJeKe()
{
    xIeJeIe->useUniqueDispIeJeKe();
    yIeJeIe->useUniqueDispIeJeKe();
}

void DistancexyConstraintIeJe::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    ConstraintIeJe::postInput();
}

void DistancexyConstraintIeJe::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void DistancexyConstraintIeJe::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void DistancexyConstraintIeJe::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void DistancexyConstraintIeJe::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType DistancexyConstraintIeJe::type()
{
    return displacement;
}

void DistancexyConstraintIeJe::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    yIeJeIe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DistancexyConstraintIeJe::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    yIeJeIe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void DistancexyConstraintIeJe::preDynOutput()
{
    xIeJeIe->preDynOutput();
    yIeJeIe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void DistancexyConstraintIeJe::postDynOutput()
{
    xIeJeIe->postDynOutput();
    yIeJeIe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
