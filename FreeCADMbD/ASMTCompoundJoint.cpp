/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTCompoundJoint.h"
#include "CompoundJoint.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTCompoundJoint> ASMTCompoundJoint::With()
{
    auto inst = std::make_shared<ASMTCompoundJoint>();
    inst->initialize();
    return inst;
}

void ASMTCompoundJoint::parseASMT(std::vector<std::string>& lines)
{
    ASMTJoint::parseASMT(lines);
    readDistanceIJ(lines);
}

void ASMTCompoundJoint::readDistanceIJ(std::vector<std::string>& lines)
{
    if (lines[0].find("distanceIJ") == std::string::npos) {
        distanceIJ = 0.0;
    }
    else {
        lines.erase(lines.begin());
        distanceIJ = readDouble(lines[0]);
        lines.erase(lines.begin());
    }
}

void ASMTCompoundJoint::createMbD()
{
    ASMTJoint::createMbD();
    auto compoundJoint = std::static_pointer_cast<CompoundJoint>(mbdObject);
    compoundJoint->distanceIJ = distanceIJ * asmtUnits()->length;
}

void ASMTCompoundJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTJoint::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "distanceIJ");
    storeOnLevelDouble(os, level + 2, distanceIJ);
}
