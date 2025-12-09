/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIJ.h"
#include "GearConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<GearConstraintIJ> GearConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    assert(frmi->isEndFrameqc());
    assert(frmj->isEndFrameqc());
    auto inst = std::make_shared<GearConstraintIqcJqc>(frmi, frmj);
    inst->initorbitsIJ();
    return inst;
}

void GearConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initorbitsIJ();
}

void GearConstraintIJ::calcPostDynCorrectorIteration()
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
    ConstraintIJ::postInput();
}

void GearConstraintIJ::postPosICIteration()
{
    orbitIeJe->postPosICIteration();
    orbitJeIe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

void GearConstraintIJ::preAccIC()
{
    orbitIeJe->preAccIC();
    orbitJeIe->preAccIC();
    ConstraintIJ::preAccIC();
}

void GearConstraintIJ::prePosIC()
{
    orbitIeJe->prePosIC();
    orbitJeIe->prePosIC();
    ConstraintIJ::prePosIC();
}

void GearConstraintIJ::preVelIC()
{
    orbitIeJe->preVelIC();
    orbitJeIe->preVelIC();
    ConstraintIJ::preVelIC();
}

double GearConstraintIJ::ratio()
{
    return radiusI / radiusJ;
}

void GearConstraintIJ::simUpdateAll()
{
    orbitIeJe->simUpdateAll();
    orbitJeIe->simUpdateAll();
    ConstraintIJ::simUpdateAll();
}

void GearConstraintIJ::postDynPredictor()
{
    orbitIeJe->postDynPredictor();
    orbitJeIe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void GearConstraintIJ::postDynCorrectorIteration()
{
    orbitIeJe->postDynCorrectorIteration();
    orbitJeIe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void GearConstraintIJ::preDynOutput()
{
    orbitIeJe->preDynOutput();
    orbitJeIe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void GearConstraintIJ::postDynOutput()
{
    orbitIeJe->postDynOutput();
    orbitJeIe->postDynOutput();
    ConstraintIJ::postDynOutput();
}
