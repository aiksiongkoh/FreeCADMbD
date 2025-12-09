/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTSphSphJoint.h"
#include "SphSphJoint.h"

using namespace MbD;

std::shared_ptr<ASMTSphSphJoint> ASMTSphSphJoint::With()
{
    auto inst = std::make_shared<ASMTSphSphJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTSphSphJoint::mbdClassNew()
{
    return SphSphJoint::With();
}
