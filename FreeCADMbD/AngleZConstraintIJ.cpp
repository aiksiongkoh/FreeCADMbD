/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIJ.h"
#include "AngleZConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<AngleZConstraintIJ> AngleZConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto angleZConIJ = std::make_shared<AngleZConstraintIqcJqc>(frmi, frmj);
    angleZConIJ->initialize();
    return angleZConIJ;
}

void AngleZConstraintIJ::calcPostDynCorrectorIteration()
{
    auto thez = thezIeJe->value();
    aG = thez - aConstant;
}

void AngleZConstraintIJ::initthezIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void AngleZConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
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
    ConstraintIJ::postInput();
}

void AngleZConstraintIJ::postPosICIteration()
{
    thezIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void AngleZConstraintIJ::preAccIC()
{
    thezIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}

void AngleZConstraintIJ::prePosIC()
{
    thezIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void AngleZConstraintIJ::preVelIC()
{
    thezIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void AngleZConstraintIJ::simUpdateAll()
{
    thezIeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

ConstraintType AngleZConstraintIJ::type()
{
    return essential;
}

std::string AngleZConstraintIJ::constraintSpec()
{
    return "AngleZConstraintIJ";
}
