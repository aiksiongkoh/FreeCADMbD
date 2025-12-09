/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTCylSphJoint.h"
#include "CylSphJoint.h"

using namespace MbD;

std::shared_ptr<ASMTCylSphJoint> ASMTCylSphJoint::With()
{
    auto inst = std::make_shared<ASMTCylSphJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTCylSphJoint::mbdClassNew()
{
    return CylSphJoint::With();
}
