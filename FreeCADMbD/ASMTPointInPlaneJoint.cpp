/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTPointInPlaneJoint.h"
#include "PointInPlaneJoint.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTPointInPlaneJoint> ASMTPointInPlaneJoint::With()
{
    auto inst = std::make_shared<ASMTPointInPlaneJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTPointInPlaneJoint::mbdClassNew()
{
    return PointInPlaneJoint::With();
}

void ASMTPointInPlaneJoint::parseASMT(std::vector<std::string>& lines)
{
    ASMTJoint::parseASMT(lines);
    readOffset(lines);
}

void ASMTPointInPlaneJoint::readOffset(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "offset");
    offset = readDouble(lines[0]);
    lines.erase(lines.begin());

}

void ASMTPointInPlaneJoint::createMbD()
{
    ASMTJoint::createMbD();
    auto pointInPlaneJoint = std::static_pointer_cast<PointInPlaneJoint>(mbdObject);
    pointInPlaneJoint->offset = offset * asmtUnits()->length;
}

void ASMTPointInPlaneJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "PointInPlaneJoint");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTPointInPlaneJoint::storeOnTimeSeries(std::ofstream& os)
{
    os << "PointInPlaneJointSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

