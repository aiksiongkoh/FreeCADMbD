/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIJ.h"
#include "DistanceConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIJ> DistanceConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<DistanceConstraintIqcJqc>(frmi, frmj);
    inst->init_distIeJe();
    return inst;
}

void DistanceConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    init_distIeJe();
}

void DistanceConstraintIJ::calcPostDynCorrectorIteration()
{
aG = distIeJe->value() - aConstant;
}

void DistanceConstraintIJ::init_distIeJe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistanceConstraintIJ::initializeGlobally()
{
    distIeJe->initializeGlobally();
}

void DistanceConstraintIJ::initializeLocally()
{
    distIeJe->initializeLocally();
}

void DistanceConstraintIJ::postInput()
{
    distIeJe->postInput();
    ConstraintIJ::postInput();
}

void DistanceConstraintIJ::postPosICIteration()
{
    distIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void DistanceConstraintIJ::preAccIC()
{
    distIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}

void DistanceConstraintIJ::prePosIC()
{
    distIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void DistanceConstraintIJ::preVelIC()
{
    distIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void DistanceConstraintIJ::simUpdateAll()
{
    distIeJe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

ConstraintType DistanceConstraintIJ::type()
{
    return ConstraintType::displacement;
}

void DistanceConstraintIJ::postDynPredictor()
{
    distIeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void DistanceConstraintIJ::postDynCorrectorIteration()
{
    distIeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void DistanceConstraintIJ::preDynOutput()
{
    distIeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void DistanceConstraintIJ::postDynOutput()
{
    distIeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}
