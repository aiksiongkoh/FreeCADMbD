/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIJ.h"
#include "GearConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<GearConstraintIJ> GearConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameq());
    assert(frmj->isEndFrameq());
    auto inst = std::make_shared<GearConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIJ::initialize()
{
    ConstraintIeJe::initialize();
    initorbitsIJ();
}

void GearConstraintIJ::simUpdateAll()
{
    aG = orbitJeIe->value() + (ratio() * orbitIeJe->value()) - aConstant;
}

void GearConstraintIJ::initializeGlobally()
{
    orbitIeJe->initializeGlobally();
    orbitJeIe->initializeGlobally();
}

void GearConstraintIJ::initializeLocally()
{
    orbitIeJe->initializeLocally();
    orbitJeIe->initializeLocally();
}

void GearConstraintIJ::useUniqueDispIeJeO()
{
    orbitIeJe->useUniqueDispIeJeO();
    orbitJeIe->useUniqueDispIeJeO();
}

void GearConstraintIJ::useUniqueDispIeJeKe()
{
    orbitIeJe->useUniqueDispIeJeKe();
    orbitJeIe->useUniqueDispIeJeKe();
}

void GearConstraintIJ::initorbitsIJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void GearConstraintIJ::postInput()
{
    orbitIeJe->postInput();
    orbitJeIe->postInput();
    if (aConstant == std::numeric_limits<double>::min()) {
        aConstant = orbitJeIe->value() + (ratio() * orbitIeJe->value());
    }
    ConstraintIeJe::postInput();
}

void GearConstraintIJ::postPosICIteration()
{
    orbitIeJe->postPosICIteration();
    orbitJeIe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void GearConstraintIJ::preAccIC()
{
    orbitIeJe->preAccIC();
    orbitJeIe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void GearConstraintIJ::prePosIC()
{
    orbitIeJe->prePosIC();
    orbitJeIe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void GearConstraintIJ::preVelIC()
{
    orbitIeJe->preVelIC();
    orbitJeIe->preVelIC();
    ConstraintIeJe::preVelIC();
}

double GearConstraintIJ::ratio()
{
    return radiusI / radiusJ;
}

void GearConstraintIJ::postDynPredictor()
{
    orbitIeJe->postDynPredictor();
    orbitJeIe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void GearConstraintIJ::postDynCorrectorIteration()
{
    orbitIeJe->postDynCorrectorIteration();
    orbitJeIe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void GearConstraintIJ::preDynOutput()
{
    orbitIeJe->preDynOutput();
    orbitJeIe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void GearConstraintIJ::postDynOutput()
{
    orbitIeJe->postDynOutput();
    orbitJeIe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}
