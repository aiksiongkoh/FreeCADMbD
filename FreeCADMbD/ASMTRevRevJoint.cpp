/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTRevRevJoint.h"
#include "RevRevJoint.h"

using namespace MbD;

std::shared_ptr<ASMTRevRevJoint> ASMTRevRevJoint::With()
{
    auto inst = std::make_shared<ASMTRevRevJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTRevRevJoint::mbdClassNew()
{
    return RevRevJoint::With();
}
