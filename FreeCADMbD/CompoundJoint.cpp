/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CompoundJoint.h"

using namespace MbD;

std::shared_ptr<CompoundJoint> CompoundJoint::With()
{
    auto inst = std::make_shared<CompoundJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<CompoundJoint> CompoundJoint::With(const std::string& str)
{
    auto inst = std::make_shared<CompoundJoint>(str);
    inst->initialize();
    return inst;
}
