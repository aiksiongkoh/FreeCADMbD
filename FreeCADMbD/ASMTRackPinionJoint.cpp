/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTRackPinionJoint.h"
#include "RackPinJoint.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTRackPinionJoint> ASMTRackPinionJoint::With()
{
    auto inst = std::make_shared<ASMTRackPinionJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTRackPinionJoint::mbdClassNew()
{
    return RackPinJoint::With();
}

void ASMTRackPinionJoint::parseASMT(std::vector<std::string>& lines)
{
    ASMTJoint::parseASMT(lines);
    readPitchRadius(lines);
}

void ASMTRackPinionJoint::readPitchRadius(std::vector<std::string>& lines)
{
    if (lines[0].find("pitchRadius") == std::string::npos) {
        pitchRadius = 0.0;
    }
    else {
        lines.erase(lines.begin());
        pitchRadius = readDouble(lines[0]);
        lines.erase(lines.begin());
    }
}

void ASMTRackPinionJoint::createMbD()
{
    ASMTJoint::createMbD();
    auto rackPinJoint = std::static_pointer_cast<RackPinJoint>(mbdObject);
    rackPinJoint->pitchRadius = pitchRadius * asmtUnits()->length;
}

void ASMTRackPinionJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTJoint::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "pitchRadius");
    storeOnLevelDouble(os, level + 2, pitchRadius);
    //storeOnLevelString(os, level + 1, "constant");
    //storeOnLevelDouble(os, level + 2, aConstant);
}
