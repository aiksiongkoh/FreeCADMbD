/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstVelConstraintIJ.h"
#include "DirectionCosineIecJec.h"
#include "ConstVelConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ConstVelConstraintIJ> ConstVelConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<ConstVelConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ConstVelConstraintIJ::initialize()
{
    initA01IeJe();
    initA10IeJe();
}

void ConstVelConstraintIJ::calcPostDynCorrectorIteration()
{
    aG = aA01IeJe->aAijIeJe + aA10IeJe->aAijIeJe - aConstant;
}

void ConstVelConstraintIJ::initA01IeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ConstVelConstraintIJ::initA10IeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void ConstVelConstraintIJ::initializeGlobally()
{
    aA01IeJe->initializeGlobally();
    aA10IeJe->initializeGlobally();
}

void ConstVelConstraintIJ::initializeLocally()
{
    aA01IeJe->initializeLocally();
    aA10IeJe->initializeLocally();
}

void ConstVelConstraintIJ::postInput()
{
    aA01IeJe->postInput();
    aA10IeJe->postInput();
    ConstraintIJ::postInput();
}

void ConstVelConstraintIJ::postPosICIteration()
{
    aA01IeJe->postPosICIteration();
    aA10IeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void ConstVelConstraintIJ::preAccIC()
{
    aA01IeJe->preAccIC();
    aA10IeJe->preAccIC();
    ConstraintIJ::preAccIC();
}

void ConstVelConstraintIJ::prePosIC()
{
    aA01IeJe->prePosIC();
    aA10IeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void ConstVelConstraintIJ::preVelIC()
{
    aA01IeJe->preVelIC();
    aA10IeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void ConstVelConstraintIJ::simUpdateAll()
{
    aA01IeJe->simUpdateAll();
    aA10IeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

void ConstVelConstraintIJ::postDynPredictor()
{
    aA01IeJe->postDynPredictor();
    aA10IeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void ConstVelConstraintIJ::postDynCorrectorIteration()
{
    aA01IeJe->postDynCorrectorIteration();
    aA10IeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void ConstVelConstraintIJ::preDynOutput()
{
    aA01IeJe->preDynOutput();
    aA10IeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void ConstVelConstraintIJ::postDynOutput()
{
    aA01IeJe->postDynOutput();
    aA10IeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}
