/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTRotationLimit.h"
#include "ASMTAssembly.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "RotationLimitIJ.h"

using namespace MbD;

std::shared_ptr<ASMTRotationLimit> ASMTRotationLimit::With()
{
    auto rotationLimit = std::make_shared<ASMTRotationLimit>();
    rotationLimit->initialize();
    return rotationLimit;
}

std::shared_ptr<ConstraintSet> ASMTRotationLimit::mbdClassNew()
{
    return RotationLimitIJ::With();
}

void ASMTRotationLimit::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RotationLimit");
    ASMTLimit::storeOnLevel(os, level);
}
