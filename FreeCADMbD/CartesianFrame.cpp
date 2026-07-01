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

bool CartesianFrame::has_qX() const
{
    //qX is vector of positional states
    return false;
}

bool CartesianFrame::has_s() const
{
    //s is vector of geometric parameter states
    return false;
}

size_t CartesianFrame::iqX() const
{
    throw SimulationStoppingError("To be implemented.");
}

size_t CartesianFrame::iqE() const
{
    throw SimulationStoppingError("To be implemented.");
}
