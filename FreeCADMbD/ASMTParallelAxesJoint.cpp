/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTParallelAxesJoint.h"
#include "ParallelAxesJoint.h"

using namespace MbD;

std::shared_ptr<ASMTParallelAxesJoint> ASMTParallelAxesJoint::With()
{
    auto inst = std::make_shared<ASMTParallelAxesJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTParallelAxesJoint::mbdClassNew()
{
    return ParallelAxesJoint::With();
}
