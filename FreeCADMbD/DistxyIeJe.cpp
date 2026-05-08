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

std::shared_ptr<DistxyIeJe> DistxyIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    auto inst = std::make_shared<DistxyIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistxyIeJe::initialize()
{
    KinematicIJ::initialize();
    init_xyIeJeIe();
}

void DistxyIeJe::simUpdateAll()
{
    //rxyIeJe = sqrt(xIeJeIe^2 + yIeJeIe^2);
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
    KinematicIJ::initializeLocally();
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
    KinematicIJ::postInput();
}

void DistxyIeJe::postPosICIteration()
{
    xIeJeIe->postPosICIteration();
    yIeJeIe->postPosICIteration();
    KinematicIJ::postPosICIteration();
}

void DistxyIeJe::preAccIC()
{
    xIeJeIe->preAccIC();
    yIeJeIe->preAccIC();
    KinematicIJ::preAccIC();
}

void DistxyIeJe::prePosIC()
{
    xIeJeIe->prePosIC();
    yIeJeIe->prePosIC();
    KinematicIJ::prePosIC();
}

void DistxyIeJe::preVelIC()
{
    xIeJeIe->preVelIC();
    yIeJeIe->preVelIC();
    KinematicIJ::preVelIC();
}

double DistxyIeJe::value()
{
    return distxy;
}
