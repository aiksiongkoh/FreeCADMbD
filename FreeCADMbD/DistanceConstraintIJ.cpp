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
    inst->initialize();
    return inst;
}

void DistanceConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    init_distIeJe();
}

void DistanceConstraintIJ::simUpdateAll()
{
    //aG = rIeJe - C;
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
    ConstraintIeJe::postInput();
}

void DistanceConstraintIJ::postPosICIteration()
{
    distIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void DistanceConstraintIJ::preAccIC()
{
    distIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void DistanceConstraintIJ::prePosIC()
{
    distIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void DistanceConstraintIJ::preVelIC()
{
    distIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType DistanceConstraintIJ::type()
{
    return ConstraintType::displacement;
}

void DistanceConstraintIJ::postDynPredictor()
{
    distIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DistanceConstraintIJ::postDynCorrectorIteration()
{
    distIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void DistanceConstraintIJ::preDynOutput()
{
    distIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void DistanceConstraintIJ::postDynOutput()
{
    distIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
