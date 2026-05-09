/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <cmath>
#include <numbers>

#include "ScrewConstraintIeJe.h"
#include "ScrewConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIeJe> ScrewConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<ScrewConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    initzIeJeIe();
    initthezIeJe();
}

void ScrewConstraintIeJe::simUpdateAll()
{
    auto z = zIeJeIe->value();
    auto thez = thezIeJe->thez;
    aG = (2.0 * std::numbers::pi * z) - (pitch * thez) - aConstant;
}

void ScrewConstraintIeJe::initzIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScrewConstraintIeJe::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScrewConstraintIeJe::initializeGlobally()
{
    zIeJeIe->initializeGlobally();
    thezIeJe->initializeGlobally();
}

void ScrewConstraintIeJe::initializeLocally()
{
    zIeJeIe->initializeLocally();
    thezIeJe->initializeLocally();
}

void ScrewConstraintIeJe::useUniqueDispIeJeO()
{
    ConstraintIeJe::useUniqueDispIeJeO();
    zIeJeIe->useUniqueDispIeJeO();
    thezIeJe->useUniqueDispIeJeO();
}

void ScrewConstraintIeJe::useUniqueDispIeJeKe()
{
    zIeJeIe->useUniqueDispIeJeKe();
    thezIeJe->useUniqueDispIeJeKe();
}

void ScrewConstraintIeJe::postInput()
{
    zIeJeIe->postInput();
    thezIeJe->postInput();
    aConstant = (2.0 * std::numbers::pi * zIeJeIe->value()) - (thezIeJe->value() * pitch);
    ConstraintIeJe::postInput();
}

void ScrewConstraintIeJe::postPosICIteration()
{
    zIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void ScrewConstraintIeJe::preAccIC()
{
    zIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void ScrewConstraintIeJe::prePosIC()
{
    zIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void ScrewConstraintIeJe::preVelIC()
{
    zIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void ScrewConstraintIeJe::postDynPredictor()
{
    zIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void ScrewConstraintIeJe::postDynCorrectorIteration()
{
    zIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void ScrewConstraintIeJe::preDynOutput()
{
    zIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void ScrewConstraintIeJe::postDynOutput()
{
    zIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
