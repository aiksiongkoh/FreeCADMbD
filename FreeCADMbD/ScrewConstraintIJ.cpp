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
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIJ> ScrewConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<ScrewConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initzIeJeIe();
    initthezIeJe();
}

void ScrewConstraintIJ::calcPostDynCorrectorIteration()
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

void ScrewConstraintIJ::postInput()
{
    zIeJeIe->postInput();
    thezIeJe->postInput();
    aConstant = (2.0 * std::numbers::pi * zIeJeIe->value()) - (thezIeJe->value() * pitch);
    ConstraintIJ::postInput();
}

void ScrewConstraintIJ::postPosICIteration()
{
    zIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void ScrewConstraintIJ::preAccIC()
{
    zIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}

void ScrewConstraintIJ::prePosIC()
{
    zIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void ScrewConstraintIJ::preVelIC()
{
    zIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void ScrewConstraintIJ::simUpdateAll()
{
    zIeJeIe->simUpdateAll();
    thezIeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

void ScrewConstraintIJ::postDynPredictor()
{
    zIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void ScrewConstraintIJ::postDynCorrectorIteration()
{
    zIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void ScrewConstraintIJ::preDynOutput()
{
    zIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void ScrewConstraintIJ::postDynOutput()
{
    zIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}
