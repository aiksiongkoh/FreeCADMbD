/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include "AtPointConstraintIJ.h"
//#include "AtPointConstraintIqcJqc.h"
#include "AtPointConstraintIqctJqc.h"
#include "DispCompIecJecO.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIJ> AtPointConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    std::shared_ptr<AtPointConstraintIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        inst = std::make_shared<AtPointConstraintIqctJqc>(frmi, frmj, axisO);
    }
    else {
        inst = std::make_shared<AtPointConstraintIqcJqc>(frmi, frmj, axisO);
    }
    inst->initialize();
    return inst;
}

void AtPointConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initriIeJeO();
}

void AtPointConstraintIJ::initializeLocally()
{
    riIeJeO->initializeLocally();
}

void AtPointConstraintIJ::initializeGlobally()
{
    riIeJeO->initializeGlobally();
}

void AtPointConstraintIJ::initriIeJeO()
{
    riIeJeO = DispCompIecJecO::With(eFrmI, eFrmJ, axis);
}

void AtPointConstraintIJ::postInput()
{
    riIeJeO->postInput();
    Constraint::postInput();
}

void AtPointConstraintIJ::calcPostDynCorrectorIteration()
{
    aG = riIeJeO->riIeJeO - aConstant;
}

void AtPointConstraintIJ::prePosIC()
{
    riIeJeO->prePosIC();
    Constraint::prePosIC();
}

ConstraintType AtPointConstraintIJ::type()
{
    return displacement;
}

void AtPointConstraintIJ::postDynPredictor()
{
    riIeJeO->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void AtPointConstraintIJ::postDynCorrectorIteration()
{
    riIeJeO->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void AtPointConstraintIJ::preDynOutput()
{
    riIeJeO->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void AtPointConstraintIJ::postDynOutput()
{
    riIeJeO->postDynOutput();
    ConstraintIJ::postDynOutput();
}

void AtPointConstraintIJ::postPosICIteration()
{
    riIeJeO->postPosICIteration();
    Item::postPosICIteration();
}

void AtPointConstraintIJ::preVelIC()
{
    riIeJeO->preVelIC();
    Item::preVelIC();
}

void AtPointConstraintIJ::preAccIC()
{
    riIeJeO->preAccIC();
    Constraint::preAccIC();
}
