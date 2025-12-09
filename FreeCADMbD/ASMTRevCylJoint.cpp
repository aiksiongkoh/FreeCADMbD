/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTRevCylJoint.h"
#include "RevCylJoint.h"

using namespace MbD;

std::shared_ptr<ASMTRevCylJoint> ASMTRevCylJoint::With()
{
    auto inst = std::make_shared<ASMTRevCylJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTRevCylJoint::mbdClassNew()
{
    return RevCylJoint::With();
}
