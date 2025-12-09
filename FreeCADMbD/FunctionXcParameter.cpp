/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "FunctionXcParameter.h"
#include "SimulationStoppingError.h"

using namespace MbD;

FunctionXcParameter::FunctionXcParameter(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<FunctionXcParameter> FunctionXcParameter::With()
{
    auto inst = std::make_shared<FunctionXcParameter>();
    inst->initialize();
    return inst;
}
