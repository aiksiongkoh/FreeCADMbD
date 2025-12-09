/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include <cassert>

#include "FunctionFromData.h"
#include "SimulationStoppingError.h"

using namespace MbD;

FunctionFromData::FunctionFromData(Symsptr arg) : FunctionXcParameter(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<FunctionFromData> FunctionFromData::With()
{
    auto inst = std::make_shared<FunctionFromData>();
    inst->initialize();
    return inst;
}
