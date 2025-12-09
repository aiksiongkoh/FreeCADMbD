/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIecJec.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistxyIecJec> DistxyIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistxyIecJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistxyIecJec::initialize()
{
    KinematicIJ::initialize();
    init_xyIeJeIe();
}

void DistxyIecJec::calcPostDynCorrectorIteration()
{
    auto x = xIeJeIe->value();
    auto y = yIeJeIe->value();
    distxy = std::sqrt(x * x + (y * y));
}

void DistxyIecJec::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void DistxyIecJec::initializeLocally()
{
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void DistxyIecJec::init_xyIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistxyIecJec::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    KinematicIJ::postInput();
}

void DistxyIecJec::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    KinematicIJ::postPosICIteration();
}

void DistxyIecJec::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    KinematicIJ::preAccIC();
}

void DistxyIecJec::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    KinematicIJ::prePosIC();
}

void DistxyIecJec::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    KinematicIJ::preVelIC();
}

void DistxyIecJec::simUpdateAll()
{
    xIeJeIe->simUpdateAll();
    yIeJeIe->simUpdateAll();
    KinematicIJ::simUpdateAll();
}

double DistxyIecJec::value()
{
    return distxy;
}
