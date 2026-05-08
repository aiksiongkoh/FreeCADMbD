/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <cmath>
#include <numbers>

#include "ScrewConstraintIJ.h"
#include "ScrewConstraintIqcJqc.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIJ> ScrewConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<ScrewConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    initzIeJeIe();
    initthezIeJe();
}

void ScrewConstraintIJ::simUpdateAll()
{
    auto z = zIeJeIe->value();
    auto thez = thezIeJe->thez;
    aG = (2.0 * std::numbers::pi * z) - (pitch * thez) - aConstant;
}

void ScrewConstraintIJ::initzIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScrewConstraintIJ::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ScrewConstraintIJ::initializeGlobally()
{
    zIeJeIe->initializeGlobally();
    thezIeJe->initializeGlobally();
}

void ScrewConstraintIJ::initializeLocally()
{
    zIeJeIe->initializeLocally();
    thezIeJe->initializeLocally();
}

void ScrewConstraintIJ::useUniqueDispIeJeO()
{
    zIeJeIe->useUniqueDispIeJeO();
    thezIeJe->useUniqueDispIeJeO();
}

void ScrewConstraintIJ::useUniqueDispIeJeKe()
{
    zIeJeIe->useUniqueDispIeJeKe();
    thezIeJe->useUniqueDispIeJeKe();
}

void ScrewConstraintIJ::postInput()
{
    zIeJeIe->postInput();
    thezIeJe->postInput();
    aConstant = (2.0 * std::numbers::pi * zIeJeIe->value()) - (thezIeJe->value() * pitch);
    ConstraintIeJe::postInput();
}

void ScrewConstraintIJ::postPosICIteration()
{
    zIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void ScrewConstraintIJ::preAccIC()
{
    zIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void ScrewConstraintIJ::prePosIC()
{
    zIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void ScrewConstraintIJ::preVelIC()
{
    zIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void ScrewConstraintIJ::postDynPredictor()
{
    zIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void ScrewConstraintIJ::postDynCorrectorIteration()
{
    zIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void ScrewConstraintIJ::preDynOutput()
{
    zIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void ScrewConstraintIJ::postDynOutput()
{
    zIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
