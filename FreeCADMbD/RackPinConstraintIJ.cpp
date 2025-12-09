/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIJ.h"
#include "RackPinConstraintIqcJqc.h"
#include "EndFrameqc.h"
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
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<RackPinConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initxIeJeIe();
    initthezIeJe();
}

void RackPinConstraintIJ::calcPostDynCorrectorIteration()
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

void RackPinConstraintIJ::postInput()
{
    xIeJeIe->postInput();
    thezIeJe->postInput();
    if (aConstant == std::numeric_limits<double>::min()) {
        aConstant = xIeJeIe->value() + (pitchRadius * thezIeJe->value());
    }
    ConstraintIJ::postInput();
}

void RackPinConstraintIJ::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void RackPinConstraintIJ::preAccIC()
{
    xIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}

void RackPinConstraintIJ::prePosIC()
{
    xIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void RackPinConstraintIJ::preVelIC()
{
    xIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void RackPinConstraintIJ::simUpdateAll()
{
    xIeJeIe->simUpdateAll();
    thezIeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

void RackPinConstraintIJ::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void RackPinConstraintIJ::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void RackPinConstraintIJ::preDynOutput()
{
    xIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void RackPinConstraintIJ::postDynOutput()
{
    xIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}

std::string RackPinConstraintIJ::constraintSpec()
{
    return "RackPinConstraintIJ";
}
