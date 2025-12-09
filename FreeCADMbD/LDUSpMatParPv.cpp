/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "LDUSpMatParPv.h"

using namespace MbD;

std::shared_ptr<LDUSpMatParPv> LDUSpMatParPv::With()
{
    auto inst = std::make_shared<LDUSpMatParPv>();
    inst->initialize();
    return inst;
}
