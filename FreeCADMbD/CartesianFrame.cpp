/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CartesianFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

CartesianFrame::CartesianFrame(const std::string& str) : Item(str)
{
    //Do nothing.
}

std::shared_ptr<CartesianFrame> CartesianFrame::With(const std::string& str)
{
    auto inst = std::make_shared<CartesianFrame>(str);
    inst->initialize();
    return inst;
}

void CartesianFrame::initialize()
{
    throw SimulationStoppingError("To be implemented.");
}
