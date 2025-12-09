/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>

#include "SingularMatrixError.h"

using namespace MbD;

#include "LDUFullMatParPvRobust.h"

std::shared_ptr<LDUFullMatParPvRobust> LDUFullMatParPvRobust::With()
{
    auto inst = std::make_shared<LDUFullMatParPvRobust>();
    inst->initialize();
    return inst;
}

void LDUFullMatParPvRobust::doPivoting(size_t p)
{
    try {
        LDUFullMatParPv::doPivoting(p);
    }
    catch (SingularMatrixError ex) {
        //Resume
    }
}
