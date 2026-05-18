/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ConstVelConstraintIeJe.h"
#include "DirectionCosineIeJe.h"
#include "ConstVelConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void ConstVelConstraintIeJe::postStaticIteration()
{
    aA01IeJe->postStaticIteration();
    aA10IeJe->postStaticIteration();
    ConstraintIeJe::postStaticIteration();
}

void ConstVelConstraintIeJe::preStatic()
{
    aA01IeJe->preStatic();
    aA10IeJe->preStatic();
    ConstraintIeJe::preStatic();
}

std::shared_ptr<ConstVelConstraintIeJe> ConstVelConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<ConstVelConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ConstVelConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    initA01IeJe();
    initA10IeJe();
}

void ConstVelConstraintIeJe::simUpdateAll()
{
    // aG = aA01IeJe + aA10IeJe - aConstant;
    aG = aA01IeJe->aAijIeJe + aA10IeJe->aAijIeJe - aConstant;
}

void ConstVelConstraintIeJe::initA01IeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ConstVelConstraintIeJe::initA10IeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ConstVelConstraintIeJe::initializeGlobally()
{
    aA01IeJe->initializeGlobally();
    aA10IeJe->initializeGlobally();
}

void ConstVelConstraintIeJe::initializeLocally()
{
    aA01IeJe->initializeLocally();
    aA10IeJe->initializeLocally();
}

void ConstVelConstraintIeJe::postInput()
{
    aA01IeJe->postInput();
    aA10IeJe->postInput();
    ConstraintIeJe::postInput();
}

void ConstVelConstraintIeJe::postPosICIteration()
{
    aA01IeJe->postPosICIteration();
    aA10IeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void ConstVelConstraintIeJe::preAccIC()
{
    aA01IeJe->preAccIC();
    aA10IeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void ConstVelConstraintIeJe::prePosIC()
{
    aA01IeJe->prePosIC();
    aA10IeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void ConstVelConstraintIeJe::preVelIC()
{
    aA01IeJe->preVelIC();
    aA10IeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void ConstVelConstraintIeJe::postDynPredictor()
{
    aA01IeJe->postDynPredictor();
    aA10IeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void ConstVelConstraintIeJe::postDynCorrectorIteration()
{
    aA01IeJe->postDynCorrectorIteration();
    aA10IeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void ConstVelConstraintIeJe::preDynOutput()
{
    aA01IeJe->preDynOutput();
    aA10IeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void ConstVelConstraintIeJe::postDynOutput()
{
    aA01IeJe->postDynOutput();
    aA10IeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

void ConstVelConstraintIeJe::addToJointForceI(FColDsptr col)
{
    // aFIeO = lam * pGpXI
    // aFIeO = lam * zero
    // Do nothing.
}

void ConstVelConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
}
