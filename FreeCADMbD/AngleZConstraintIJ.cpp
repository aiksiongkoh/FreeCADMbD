/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIJ.h"
#include "AngleZConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<AngleZConstraintIJ> AngleZConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<AngleZConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZConstraintIJ::simUpdateAll()
{
    //aG = thezIeJe - C
    auto thez = thezIeJe->value();
    aG = thez - aConstant;
}

void AngleZConstraintIJ::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * zero
    //Do nothing.
}

void AngleZConstraintIJ::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void AngleZConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    this->initthezIeJe();
}

void AngleZConstraintIJ::initializeGlobally()
{
    thezIeJe->initializeGlobally();
}

void AngleZConstraintIJ::initializeLocally()
{
    thezIeJe->initializeLocally();
}

void AngleZConstraintIJ::postInput()
{
    assert(aConstant != std::numeric_limits<double>::min());
    ConstraintIeJe::postInput();
}

void AngleZConstraintIJ::postPosICIteration()
{
    thezIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void AngleZConstraintIJ::preAccIC()
{
    thezIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void AngleZConstraintIJ::prePosIC()
{
    thezIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void AngleZConstraintIJ::preVelIC()
{
    thezIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType AngleZConstraintIJ::type()
{
    return essential;
}

std::string AngleZConstraintIJ::constraintSpec()
{
    return "AngleZConstraintIJ";
}
