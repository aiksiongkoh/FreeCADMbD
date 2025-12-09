/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTNoRotationJoint.h"
#include "NoRotationJoint.h"

using namespace MbD;

std::shared_ptr<ASMTNoRotationJoint> ASMTNoRotationJoint::With()
{
    auto inst = std::make_shared<ASMTNoRotationJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTNoRotationJoint::mbdClassNew()
{
    return NoRotationJoint::With();
}

void ASMTNoRotationJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "NoRotationJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTNoRotationJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "NoRotationJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
