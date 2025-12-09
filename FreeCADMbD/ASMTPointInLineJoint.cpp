/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTPointInLineJoint.h"
#include "PointInLineJoint.h"

using namespace MbD;

std::shared_ptr<ASMTPointInLineJoint> ASMTPointInLineJoint::With()
{
    auto inst = std::make_shared<ASMTPointInLineJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTPointInLineJoint::mbdClassNew()
{
    return PointInLineJoint::With();
}

void ASMTPointInLineJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "PointInLineJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTPointInLineJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "PointInLineJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
