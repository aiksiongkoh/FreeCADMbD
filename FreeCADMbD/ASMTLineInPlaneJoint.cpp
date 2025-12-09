/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTLineInPlaneJoint.h"
#include "LineInPlaneJoint.h"

using namespace MbD;

std::shared_ptr<ASMTLineInPlaneJoint> ASMTLineInPlaneJoint::With()
{
    auto inst = std::make_shared<ASMTLineInPlaneJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTLineInPlaneJoint::mbdClassNew()
{
    return LineInPlaneJoint::With();
}
