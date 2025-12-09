/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "StateData.h"

using namespace MbD;

std::shared_ptr<StateData> StateData::With()
{
    auto inst = std::make_shared<StateData>();
    inst->initialize();
    return inst;
}

void StateData::initialize()
{
    //Do nothing.
}
