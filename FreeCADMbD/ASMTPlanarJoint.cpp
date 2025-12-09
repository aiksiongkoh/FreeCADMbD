/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTPlanarJoint.h"
#include "PlanarJoint.h"

using namespace MbD;

std::shared_ptr<ASMTPlanarJoint> ASMTPlanarJoint::With()
{
    auto inst = std::make_shared<ASMTPlanarJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTPlanarJoint::mbdClassNew()
{
    return PlanarJoint::With();
}
