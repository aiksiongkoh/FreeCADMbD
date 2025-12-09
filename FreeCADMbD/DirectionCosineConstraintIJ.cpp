/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include "DirectionCosineConstraintIJ.h"
#include "DirectionCosineConstraintIqctJqc.h"
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIJ> DirectionCosineConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineConstraintIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        inst = std::make_shared<DirectionCosineConstraintIqctJqc>(frmi, frmj, axisi, axisj);
    }
    else {
        inst = std::make_shared<DirectionCosineConstraintIqcJqc>(frmi, frmj, axisi, axisj);
    }
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initaAijIeJe();
}

void DirectionCosineConstraintIJ::initializeLocally()
{
    aAijIeJe->initializeLocally();
}

void DirectionCosineConstraintIJ::initializeGlobally()
{
    aAijIeJe->initializeGlobally();
}

void DirectionCosineConstraintIJ::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIecJec::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIJ::postInput()
{
    aAijIeJe->postInput();
    ConstraintIJ::postInput();
}

void DirectionCosineConstraintIJ::calcPostDynCorrectorIteration()
{
    aG = aAijIeJe->aAijIeJe - aConstant;
}

void DirectionCosineConstraintIJ::prePosIC()
{
    aAijIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void DirectionCosineConstraintIJ::postPosICIteration()
{
    aAijIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

ConstraintType DirectionCosineConstraintIJ::type()
{
    return perpendicular;
}

void DirectionCosineConstraintIJ::postDynPredictor()
{
    aAijIeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void DirectionCosineConstraintIJ::postDynCorrectorIteration()
{
    aAijIeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void DirectionCosineConstraintIJ::preDynOutput()
{
    aAijIeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void DirectionCosineConstraintIJ::postDynOutput()
{
    aAijIeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}

void DirectionCosineConstraintIJ::preVelIC()
{
    aAijIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void DirectionCosineConstraintIJ::simUpdateAll()
{
    aAijIeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

void DirectionCosineConstraintIJ::preAccIC()
{
    aAijIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}
