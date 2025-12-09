/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTScrewJoint.h"
#include "ScrewJoint.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTScrewJoint> ASMTScrewJoint::With()
{
    auto inst = std::make_shared<ASMTScrewJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ConstraintSet> ASMTScrewJoint::mbdClassNew()
{
    return ScrewJoint::With();
}

void ASMTScrewJoint::parseASMT(std::vector<std::string>& lines)
{
    ASMTJoint::parseASMT(lines);
    readPitch(lines);
}

void ASMTScrewJoint::readPitch(std::vector<std::string>& lines)
{
    if (lines[0].find("pitch") == std::string::npos) {
        pitch = 0.0;
    }
    else {
        lines.erase(lines.begin());
        pitch = readDouble(lines[0]);
        lines.erase(lines.begin());
    }
}

void ASMTScrewJoint::createMbD()
{
    ASMTJoint::createMbD();
    auto screwJoint = std::static_pointer_cast<ScrewJoint>(mbdObject);
    screwJoint->pitch = pitch * asmtUnits()->length;
}

void ASMTScrewJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTJoint::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "pitch");
    storeOnLevelDouble(os, level + 2, pitch);
    //storeOnLevelString(os, level + 1, "constant");
    //storeOnLevelDouble(os, level + 2, aConstant);
}
