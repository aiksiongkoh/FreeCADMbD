/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "IndependentVariable.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<IndependentVariable> IndependentVariable::With()
{
    auto inst = std::make_shared<IndependentVariable>();
    inst->initialize();
    return inst;
}

Symsptr IndependentVariable::differentiateWRT(Symsptr var)
{
    if (this == var.get()) {
        return sptrConstant(1.0);
    }
    else {
        return sptrConstant(0.0);
    }
}
