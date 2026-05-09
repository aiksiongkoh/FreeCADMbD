/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIeJe.h"
#include "GearConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<GearConstraintIeJe> GearConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<GearConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    initorbitsIJ();
}

void GearConstraintIeJe::simUpdateAll()
{
    aG = orbitJeIe->value() + (ratio() * orbitIeJe->value()) - aConstant;
}

void GearConstraintIeJe::initializeGlobally()
{
    orbitIeJe->initializeGlobally();
    orbitJeIe->initializeGlobally();
}

void GearConstraintIeJe::initializeLocally()
{
    orbitIeJe->initializeLocally();
    orbitJeIe->initializeLocally();
}

void GearConstraintIeJe::useUniqueDispIeJeO()
{
    ConstraintIeJe::useUniqueDispIeJeO();
    orbitIeJe->useUniqueDispIeJeO();
    orbitJeIe->useUniqueDispIeJeO();
}

void GearConstraintIeJe::useUniqueDispIeJeKe()
{
    ConstraintIeJe::useUniqueDispIeJeKe();
    orbitIeJe->useUniqueDispIeJeKe();
    orbitJeIe->useUniqueDispIeJeKe();
}

void GearConstraintIeJe::initorbitsIJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void GearConstraintIeJe::postInput()
{
    orbitIeJe->postInput();
    orbitJeIe->postInput();
    if (aConstant == std::numeric_limits<double>::min()) {
        aConstant = orbitJeIe->value() + (ratio() * orbitIeJe->value());
    }
    ConstraintIeJe::postInput();
}

void GearConstraintIeJe::postPosICIteration()
{
    orbitIeJe->postPosICIteration();
    orbitJeIe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void GearConstraintIeJe::preAccIC()
{
    orbitIeJe->preAccIC();
    orbitJeIe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void GearConstraintIeJe::prePosIC()
{
    orbitIeJe->prePosIC();
    orbitJeIe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void GearConstraintIeJe::preVelIC()
{
    orbitIeJe->preVelIC();
    orbitJeIe->preVelIC();
    ConstraintIeJe::preVelIC();
}

double GearConstraintIeJe::ratio()
{
    return radiusI / radiusJ;
}

void GearConstraintIeJe::postDynPredictor()
{
    orbitIeJe->postDynPredictor();
    orbitJeIe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void GearConstraintIeJe::postDynCorrectorIteration()
{
    orbitIeJe->postDynCorrectorIteration();
    orbitJeIe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void GearConstraintIeJe::preDynOutput()
{
    orbitIeJe->preDynOutput();
    orbitJeIe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void GearConstraintIeJe::postDynOutput()
{
    orbitIeJe->postDynOutput();
    orbitJeIe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
