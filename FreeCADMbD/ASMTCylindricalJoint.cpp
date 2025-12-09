/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTCylindricalJoint.h"
#include "CylindricalJoint.h"

using namespace MbD;

std::shared_ptr<ASMTCylindricalJoint> ASMTCylindricalJoint::With()
{
    auto inst = std::make_shared<ASMTCylindricalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTCylindricalJoint::mbdClassNew()
{
    return CylindricalJoint::With();
}

void ASMTCylindricalJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "CylindricalJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTCylindricalJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "CylindricalJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
