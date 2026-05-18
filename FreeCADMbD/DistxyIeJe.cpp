/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistxyIeJe.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void DistxyIeJe::preStatic()
{
    xIeJeIe->preStatic();
    yIeJeIe->preStatic();
    KinematicIeJe::preStatic();
}

std::shared_ptr<DistxyIeJe> DistxyIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    auto inst = std::make_shared<DistxyIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistxyIeJe::initialize()
{
    KinematicIeJe::initialize();
    init_xyIeJeIe();
}

void DistxyIeJe::simUpdateAll()
{
    // rxyIeJe = sqrt(xIeJeIe^2 + yIeJeIe^2);
    auto x = xIeJeIe->value();
    auto y = yIeJeIe->value();
    distxy = std::sqrt(x * x + (y * y));
}

void DistxyIeJe::initializeGlobally()
{
    xIeJeIe->initializeGlobally();
    yIeJeIe->initializeGlobally();
}

void DistxyIeJe::initializeLocally()
{
    KinematicIeJe::initializeLocally();
    xIeJeIe->initializeLocally();
    yIeJeIe->initializeLocally();
}

void DistxyIeJe::useUniqueDispIeJeO()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistxyIeJe::useUniqueDispIeJeKe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistxyIeJe::init_xyIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

void DistxyIeJe::postInput()
{
    xIeJeIe->postInput();
    yIeJeIe->postInput();
    KinematicIeJe::postInput();
}

void DistxyIeJe::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    KinematicIeJe::postPosICIteration();
}

void DistxyIeJe::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    KinematicIeJe::preAccIC();
}

void DistxyIeJe::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    KinematicIeJe::prePosIC();
}

void DistxyIeJe::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    KinematicIeJe::preVelIC();
}

double DistxyIeJe::value()
{
    return distxy;
}
