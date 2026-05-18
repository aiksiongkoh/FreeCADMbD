/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIeJe.h"
#include "AngleZConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void AngleZConstraintIeJe::preStatic()
{
    thezIeJe->preStatic();
    ConstraintIeJe::preStatic();
}

std::shared_ptr<AngleZConstraintIeJe> AngleZConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<AngleZConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZConstraintIeJe::simUpdateAll()
{
    // aG = thezIeJe - C
    auto thez = thezIeJe->value();
    aG = thez - aConstant;
}

void AngleZConstraintIeJe::addToJointForceI(FColDsptr col)
{
    // aFIeO = lam * pGpXI
    // aFIeO = lam * zero
    // Do nothing.
}

void AngleZConstraintIeJe::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void AngleZConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    this->initthezIeJe();
}

void AngleZConstraintIeJe::initializeGlobally()
{
    thezIeJe->initializeGlobally();
}

void AngleZConstraintIeJe::initializeLocally()
{
    thezIeJe->initializeLocally();
}

void AngleZConstraintIeJe::postInput()
{
    assert(aConstant != std::numeric_limits<double>::min());
    ConstraintIeJe::postInput();
}

void AngleZConstraintIeJe::postPosICIteration()
{
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void AngleZConstraintIeJe::preAccIC()
{
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void AngleZConstraintIeJe::prePosIC()
{
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void AngleZConstraintIeJe::preVelIC()
{
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType AngleZConstraintIeJe::type()
{
    return essential;
}

std::string AngleZConstraintIeJe::constraintSpec()
{
    return "AngleZConstraintIeJe";
}
