/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIJ.h"
#include "RackPinConstraintIqcJqc.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIJ> RackPinConstraintIJ::With()
{
    auto inst = std::make_shared<RackPinConstraintIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RackPinConstraintIJ> RackPinConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<RackPinConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    initxIeJeIe();
    initthezIeJe();
}

void RackPinConstraintIJ::simUpdateAll()
{
    auto x = xIeJeIe->value();
    auto thez = thezIeJe->value();
    aG = x + (pitchRadius * thez) - aConstant;
}

void RackPinConstraintIJ::initxIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void RackPinConstraintIJ::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void RackPinConstraintIJ::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    thezIeJe->initializeGlobally();
}

void RackPinConstraintIJ::initializeLocally()
{
    xIeJeIe->initializeLocally();
    thezIeJe->initializeLocally();
}

void RackPinConstraintIJ::useUniqueDispIeJeO()
{
    xIeJeIe->useUniqueDispIeJeO();
    thezIeJe->useUniqueDispIeJeO();
}

void RackPinConstraintIJ::useUniqueDispIeJeKe()
{
    xIeJeIe->useUniqueDispIeJeKe();
    thezIeJe->useUniqueDispIeJeKe();
}

void RackPinConstraintIJ::postInput()
{
    xIeJeIe->postInput();
    thezIeJe->postInput();
    if (aConstant == std::numeric_limits<double>::min()) {
        aConstant = xIeJeIe->value() + (pitchRadius * thezIeJe->value());
    }
    ConstraintIeJe::postInput();
}

void RackPinConstraintIJ::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void RackPinConstraintIJ::preAccIC()
{
    xIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void RackPinConstraintIJ::prePosIC()
{
    xIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void RackPinConstraintIJ::preVelIC()
{
    xIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void RackPinConstraintIJ::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void RackPinConstraintIJ::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void RackPinConstraintIJ::preDynOutput()
{
    xIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void RackPinConstraintIJ::postDynOutput()
{
    xIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

std::string RackPinConstraintIJ::constraintSpec()
{
    return "RackPinConstraintIJ";
}
