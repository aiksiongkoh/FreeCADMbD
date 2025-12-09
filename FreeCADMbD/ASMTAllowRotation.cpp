/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTAllowRotation.h"
#include "ASMTAssembly.h"
#include "ASMTJoint.h"
#include "AllowZRotation.h"

using namespace MbD;

std::shared_ptr<ASMTAllowRotation> ASMTAllowRotation::With()
{
    auto inst = std::make_shared<ASMTAllowRotation>();
    inst->initialize();
    return inst;
}

void ASMTAllowRotation::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    if (lines[0].find("MarkerI") != std::string::npos) {
        readMarkerI(lines);
        readMarkerJ(lines);
    }
    readMotionJoint(lines);
}

void ASMTAllowRotation::readMotionJoint(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MotionJoint");
    motionJoint = readStringNoSpacesOffTop(lines);
}

void ASMTAllowRotation::initMarkers()
{
    if (motionJoint == "") {
        assert(markerI->name != "");
        assert(markerJ->name != "");
    }
    else {
        auto jt = root()->jointAt(motionJoint);
        markerI = jt->markerI;
        markerJ = jt->markerJ;
    }
}

std::shared_ptr<ConstraintSet> ASMTAllowRotation::mbdClassNew()
{
    return AllowZRotation::With();
}

void ASMTAllowRotation::setMotionJoint(const std::string& motionJoint)
{
    (void) motionJoint;
}

void ASMTAllowRotation::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "AllowRotation");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "MotionJoint");
    storeOnLevelString(os, level + 2, motionJoint);
}

void ASMTAllowRotation::storeOnTimeSeries(std::ofstream& os)
{
    os << "AllowRotationSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
