/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "RackPinConstraintIeJe.h"
#include "RackPinConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void RackPinConstraintIeJe::postStaticIteration()
{
    xIeJeIe->postStaticIteration();
    thezIeJe->postStaticIteration();
    ConstraintIeJe::postStaticIteration();
}

void RackPinConstraintIeJe::preStatic()
{
    xIeJeIe->preStatic();
    thezIeJe->preStatic();
    ConstraintIeJe::preStatic();
}

std::shared_ptr<RackPinConstraintIeJe> RackPinConstraintIeJe::With()
{
    auto inst = std::make_shared<RackPinConstraintIeJe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RackPinConstraintIeJe> RackPinConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<RackPinConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    initxIeJeIe();
    initthezIeJe();
}

void RackPinConstraintIeJe::simUpdateAll()
{
    auto x = xIeJeIe->value();
    auto thez = thezIeJe->value();
    aG = x + (pitchRadius * thez) - aConstant;
}

void RackPinConstraintIeJe::initxIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void RackPinConstraintIeJe::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void RackPinConstraintIeJe::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    thezIeJe->initializeGlobally();
}

void RackPinConstraintIeJe::initializeLocally()
{
    xIeJeIe->initializeLocally();
    thezIeJe->initializeLocally();
}

void RackPinConstraintIeJe::useUniqueDispIeJeO()
{
    ConstraintIeJe::useUniqueDispIeJeO();
    xIeJeIe->useUniqueDispIeJeO();
    thezIeJe->useUniqueDispIeJeO();
}

void RackPinConstraintIeJe::useUniqueDispIeJeKe()
{
    ConstraintIeJe::useUniqueDispIeJeKe();
    xIeJeIe->useUniqueDispIeJeKe();
    thezIeJe->useUniqueDispIeJeKe();
}

void RackPinConstraintIeJe::postInput()
{
    xIeJeIe->postInput();
    thezIeJe->postInput();
    if (aConstant == std::numeric_limits<double>::min())
    {
        aConstant = xIeJeIe->value() + (pitchRadius * thezIeJe->value());
    }
    ConstraintIeJe::postInput();
}

void RackPinConstraintIeJe::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void RackPinConstraintIeJe::preAccIC()
{
    xIeJeIe->preAccIC();
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void RackPinConstraintIeJe::prePosIC()
{
    xIeJeIe->prePosIC();
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void RackPinConstraintIeJe::preVelIC()
{
    xIeJeIe->preVelIC();
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void RackPinConstraintIeJe::postDynPredictor()
{
    xIeJeIe->postDynPredictor();
    thezIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void RackPinConstraintIeJe::postDynCorrectorIteration()
{
    xIeJeIe->postDynCorrectorIteration();
    thezIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void RackPinConstraintIeJe::preDynOutput()
{
    xIeJeIe->preDynOutput();
    thezIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void RackPinConstraintIeJe::postDynOutput()
{
    xIeJeIe->postDynOutput();
    thezIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

std::string RackPinConstraintIeJe::constraintSpec()
{
    return "RackPinConstraintIeJe";
}
