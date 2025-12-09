/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTConstantVelocityJoint.h"
#include "ConstantVelocityJoint.h"

using namespace MbD;

std::shared_ptr<ASMTConstantVelocityJoint> ASMTConstantVelocityJoint::With()
{
    auto inst = std::make_shared<ASMTConstantVelocityJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTConstantVelocityJoint::mbdClassNew()
{
    return ConstantVelocityJoint::With();
}
