/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistanceConstraintIeJe.h"
#include "DistanceConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void DistanceConstraintIeJe::postStaticIteration()
{
    distIeJe->postStaticIteration();
    ConstraintIeJe::postStaticIteration();
}

void DistanceConstraintIeJe::preStatic()
{
    distIeJe->preStatic();
    ConstraintIeJe::preStatic();
}

std::shared_ptr<DistanceConstraintIeJe> DistanceConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<DistanceConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistanceConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    init_distIeJe();
}

void DistanceConstraintIeJe::simUpdateAll()
{
    // aG = rIeJe - C;
    aG = distIeJe->value() - aConstant;
}

void DistanceConstraintIeJe::init_distIeJe()
{
    distIeJe = DistIeJe::With(eFrmI, eFrmJ);
    distIeJe->owner = this;
}

void DistanceConstraintIeJe::initializeGlobally()
{
    distIeJe->initializeGlobally();
}

void DistanceConstraintIeJe::initializeLocally()
{
    distIeJe->initializeLocally();
}

void MbD::DistanceConstraintIeJe::useUniqueDispIeJeO()
{
    ConstraintIeJe::useUniqueDispIeJeO();
    distIeJe->useUniqueDispIeJeO();
}

void MbD::DistanceConstraintIeJe::useUniqueDispIeJeKe()
{
    ConstraintIeJe::useUniqueDispIeJeKe();
    distIeJe->useUniqueDispIeJeKe();
}

void DistanceConstraintIeJe::postInput()
{
    distIeJe->postInput();
    ConstraintIeJe::postInput();
}

void DistanceConstraintIeJe::postPosICIteration()
{
    distIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void DistanceConstraintIeJe::preAccIC()
{
    distIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void DistanceConstraintIeJe::prePosIC()
{
    distIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void DistanceConstraintIeJe::preVelIC()
{
    distIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

ConstraintType DistanceConstraintIeJe::type()
{
    return ConstraintType::displacement;
}

void DistanceConstraintIeJe::postDynPredictor()
{
    distIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DistanceConstraintIeJe::postDynCorrectorIteration()
{
    distIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void DistanceConstraintIeJe::preDynOutput()
{
    distIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void DistanceConstraintIeJe::postDynOutput()
{
    distIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
