/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTSphericalJoint.h"
#include "SphericalJoint.h"

using namespace MbD;

std::shared_ptr<ASMTSphericalJoint> ASMTSphericalJoint::With()
{
    auto inst = std::make_shared<ASMTSphericalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTSphericalJoint::mbdClassNew()
{
    return SphericalJoint::With();
}

void ASMTSphericalJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "SphericalJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTSphericalJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "SphericalJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
