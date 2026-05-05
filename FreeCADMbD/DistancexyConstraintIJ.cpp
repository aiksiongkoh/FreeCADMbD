/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIJ.h"
#include "DistancexyConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIJ> DistancexyConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<DistancexyConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    init_xyIeJeIe();
}

void DistancexyConstraintIJ::simUpdateAll()
{
    //aG = xIeJeIe^2 + yIeJeIe^2 - C^2;
    auto x = xIeJeIe->value();
    auto y = yIeJeIe->value();
    aG = x * x + (y * y) - (aConstant * aConstant);
}

void DistancexyConstraintIJ::init_xyIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistancexyConstraintIJ::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void DistancexyConstraintIJ::initializeLocally()
{
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void MbD::DistancexyConstraintIJ::useUniqueDispIeJeO()
{
    xIeJeIe->useUniqueDispIeJeO();
    yIeJeIe->useUniqueDispIeJeO();
}

void MbD::DistancexyConstraintIJ::useUniqueDispIeJeKe()
{
    xIeJeIe->useUniqueDispIeJeKe();
    yIeJeIe->useUniqueDispIeJeKe();
}

void DistancexyConstraintIJ::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    ConstraintIeJe::postInput();
}

void DistancexyConstraintIJ::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void DistancexyConstraintIJ::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void DistancexyConstraintIJ::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void DistancexyConstraintIJ::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType DistancexyConstraintIJ::type()
{
    return displacement;
}

void DistancexyConstraintIJ::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    yIeJeIe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DistancexyConstraintIJ::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    yIeJeIe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void DistancexyConstraintIJ::preDynOutput()
{
    xIeJeIe->preDynOutput();
    yIeJeIe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void DistancexyConstraintIJ::postDynOutput()
{
    xIeJeIe->postDynOutput();
    yIeJeIe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
