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
    inst->init_xyIeJeIe();
    return inst;
}

void DistancexyConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    init_xyIeJeIe();
}

void DistancexyConstraintIJ::calcPostDynCorrectorIteration()
{
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

void DistancexyConstraintIJ::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    ConstraintIJ::postInput();
}

void DistancexyConstraintIJ::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void DistancexyConstraintIJ::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    ConstraintIJ::preAccIC();
}

void DistancexyConstraintIJ::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    ConstraintIJ::prePosIC();
}

void DistancexyConstraintIJ::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    ConstraintIJ::preVelIC();
}

void DistancexyConstraintIJ::simUpdateAll()
{
    xIeJeIe->simUpdateAll();
    yIeJeIe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

ConstraintType DistancexyConstraintIJ::type()
{
    return displacement;
}

void DistancexyConstraintIJ::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    yIeJeIe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void DistancexyConstraintIJ::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    yIeJeIe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void DistancexyConstraintIJ::preDynOutput()
{
    xIeJeIe->preDynOutput();
    yIeJeIe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void DistancexyConstraintIJ::postDynOutput()
{
    xIeJeIe->postDynOutput();
    yIeJeIe->postDynOutput();
    ConstraintIJ::postDynOutput();
}
