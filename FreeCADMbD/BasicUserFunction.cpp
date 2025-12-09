/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "BasicUserFunction.h"
#include "Units.h"

using namespace MbD;

BasicUserFunction::BasicUserFunction(const std::string& expression, double myUnt) : funcText(expression), myUnit(myUnt)
{
    units = std::make_shared<Units>();
}

std::shared_ptr<BasicUserFunction> BasicUserFunction::With()
{
    auto inst = std::make_shared<BasicUserFunction>();
    inst->initialize();
    return inst;
}

void BasicUserFunction::initialize()
{
    units = Units::With();
}
