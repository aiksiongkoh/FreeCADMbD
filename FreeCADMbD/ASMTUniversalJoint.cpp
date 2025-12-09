/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTUniversalJoint.h"
#include "UniversalJoint.h"

using namespace MbD;

std::shared_ptr<ASMTUniversalJoint> ASMTUniversalJoint::With()
{
    auto inst = std::make_shared<ASMTUniversalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTUniversalJoint::mbdClassNew()
{
    return UniversalJoint::With();
}

void ASMTUniversalJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "UniversalJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTUniversalJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "UniversalJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
