/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <regex>

#include "MBDynJoint.h"
#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTJoint.h"
#include "ASMTForceTorque.h"
#include "ASMTAssembly.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTSphericalJoint.h"
#include "MBDynTotalJoint.h"
#include "MBDynClampJoint.h"
#include "MBDynAxialRotationJoint.h"
#include "MBDynDriveHingeJoint.h"
#include "MBDynInLineJoint.h"
#include "MBDynInPlaneJoint.h"
#include "MBDynPrismaticJoint.h"
#include "MBDynRevoluteHingeJoint.h"
#include "MBDynRevolutePinJoint.h"
#include "MBDynSphericalHingeJoint.h"
#include "MBDynRodJoint.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynJoint> MBDynJoint::newJoint(std::string statement)
{
    if (lineHasTokens(statement, "axial ", "rotation,")) {
        return MBDynAxialRotationJoint::With();
    }
    if (lineHasTokens(statement, "clamp,")) {
        return MBDynClampJoint::With();
    }
    if (lineHasTokens(statement, "drive ", "hinge,")) {
        return MBDynDriveHingeJoint::With();
    }
    if (lineHasTokens(statement, "in ", "line,")) {
        return MBDynInLineJoint::With();
    }
    if (lineHasTokens(statement, "in ", "plane,")) {
        return MBDynInPlaneJoint::With();
    }
    if (lineHasTokens(statement, "prismatic,")) {
        return MBDynPrismaticJoint::With();
    }
    if (lineHasTokens(statement, "revolute ", "hinge,")) {
        return MBDynRevoluteHingeJoint::With();
    }
    if (lineHasTokens(statement, "revolute ", "pin,")) {
        return MBDynRevolutePinJoint::With();
    }
    if (lineHasTokens(statement, "spherical ", "hinge,")) {
        return MBDynSphericalHingeJoint::With();
    }
    if (lineHasTokens(statement, "total ", "joint,")) {
        return MBDynTotalJoint::With();
    }
    if (lineHasTokens(statement, "rod,")) {
        return MBDynRodJoint::With();
    }
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<MBDynJoint>();
}

void MBDynJoint::initialize()
{
    //Do nothing.
}

void MBDynJoint::parseMBDyn(std::string line)
{
    jointString = line;
    arguments = collectArgumentsFor("joint", line);
    readLabel(arguments);
    readJointType(arguments);
    readMarkerI(arguments);
    readMarkerJ(arguments);

}

void MBDynJoint::readJointType(std::vector<std::string>& args)
{
    joint_type = readJointTypeOffTop(args);
}

void MBDynJoint::readMarkerI(std::vector<std::string>& args)
{
    mkr1 = MBDynMarker::With();
    mkr1->owner = this;
    mkr1->nodeStr = readStringNoSpacesOffTop(args);
    auto _nodeNames = nodeNames();
    std::string nodeName;
    auto it = std::find_if(args.begin(), args.end(), [&](const std::string& s) {
        auto iss = std::istringstream(s);
        iss >> nodeName;
        if (std::find(_nodeNames.begin(), _nodeNames.end(), nodeName) != _nodeNames.end()) return true;
        return false;
        });
    auto markerArgs = std::vector<std::string>(args.begin(), it);
    args.erase(args.begin(), it);
    mkr1->parseMBDyn(markerArgs);
}

void MBDynJoint::readMarkerJ(std::vector<std::string>& args)
{
    if (args.empty()) return;
    mkr2 = MBDynMarker::With();
    mkr2->owner = this;
    mkr2->nodeStr = readStringNoSpacesOffTop(args);
    mkr2->parseMBDyn(args);
}

void MBDynJoint::readTotalJointMarkerI(std::vector<std::string>& args)
{
    mkr1 = MBDynMarker::With();
    mkr1->owner = this;
    mkr1->nodeStr = readStringNoSpacesOffTop(args);
    auto _nodeNames = nodeNames();
    std::string nodeName;
    auto it = std::find_if(args.begin(), args.end(), [&](const std::string& s) {
        auto iss = std::istringstream(s);
        iss >> nodeName;
        if (std::find(_nodeNames.begin(), _nodeNames.end(), nodeName) != _nodeNames.end()) return true;
        return false;
        });
    auto markerArgs = std::vector<std::string>(args.begin(), it);
    args.erase(args.begin(), it);
    mkr1->parseMBDynTotalJointMarker(markerArgs);
}

void MBDynJoint::readTotalJointMarkerJ(std::vector<std::string>& args)
{
    if (args.empty()) return;
    mkr2 = MBDynMarker::With();
    mkr2->owner = this;
    mkr2->nodeStr = readStringNoSpacesOffTop(args);
    mkr2->parseMBDynTotalJointMarker(args);
}

void MBDynJoint::readClampMarkerJ(std::vector<std::string>& args)
{
    if (args.empty()) return;
    mkr2 = MBDynMarker::With();
    mkr2->owner = this;
    mkr2->nodeStr = readStringNoSpacesOffTop(args);
    mkr2->parseMBDynClamp(args);
}

void MBDynJoint::readFunction(std::vector<std::string>& args)
{
    if (args.empty()) return;
    std::string str;
    auto iss = std::istringstream(args.at(0));
    iss >> str;
    if (str.find("ramp") != std::string::npos) {
        args.erase(args.begin());
        std::string slope, initValue, initTime, finalTime;
        slope = popOffTop(args);
        initTime = popOffTop(args);
        finalTime = popOffTop(args);
        initValue = popOffTop(args);
        //f = slope*(time - t0) + f0
        auto ss = std::stringstream();
        ss << slope << "*(time - " << initTime << ") + " << initValue;
        formula = ss.str();
    }
    else if (str.find("single") != std::string::npos) {
        args.erase(args.begin());
        auto vec3 = readVector3(args);
        assert(vec3->at(0) == 0 && vec3->at(1) == 0 && vec3->at(2) == 1);
        assert(readStringNoSpacesOffTop(args) == "string");
        formula = popOffTop(args);
        formula = std::regex_replace(formula, std::regex("\""), "");
    }
    else if (str.find("string") != std::string::npos) {
        args.erase(args.begin());
        formula = popOffTop(args);
        formula = std::regex_replace(formula, std::regex("\""), "");
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void MBDynJoint::readTotalJointFunction(std::vector<std::string>& args)
{
    assert(lineHasTokens(args[0], "position", "constraint"));
    args.erase(args.begin());
    assert(readStringNoSpacesOffTop(args) == "active");
    assert(readStringNoSpacesOffTop(args) == "active");
    assert(readStringNoSpacesOffTop(args) == "active");
    assert(readStringNoSpacesOffTop(args) == "null");
    assert(lineHasTokens(args[0], "orientation", "constraint"));
    args.erase(args.begin());
    assert(readStringNoSpacesOffTop(args) == "active");
    assert(readStringNoSpacesOffTop(args) == "active");
    assert(readStringNoSpacesOffTop(args) == "rotation");
    readFunction(args);
}

void MBDynJoint::createASMT()
{
    mkr1->createASMT();
    if (mkr2) mkr2->createASMT();
    auto asmtItemIJ = std::static_pointer_cast<ASMTItemIJ>(asmtItem);
    asmtItemIJ->setName(label);
    asmtItemIJ->setMarkerI(std::static_pointer_cast<ASMTMarker>(mkr1->asmtItem));
    asmtItemIJ->setMarkerJ(std::static_pointer_cast<ASMTMarker>(mkr2->asmtItem));
}

void MBDynJoint::outputLine(size_t i, std::ostream& os)
{
    auto id = labelIDat(label);
    auto asmtJoint = std::static_pointer_cast<ASMTJoint>(asmtItem);
    auto aFII = asmtJoint->aFII(i);
    auto aTII = asmtJoint->aTII(i);
    auto aFIO = asmtJoint->aFIO(i);
    auto aTIO = asmtJoint->aTIO(i);
    os << id << " ";
    os << aFII->at(0) << " " << aFII->at(1) << " " << aFII->at(2) << " ";
    os << aTII->at(0) << " " << aTII->at(1) << " " << aTII->at(2) << " ";
    os << aFIO->at(0) << " " << aFIO->at(1) << " " << aFIO->at(2) << " ";
    os << aTIO->at(0) << " " << aTIO->at(1) << " " << aTIO->at(2) << " ";
    os << std::endl;
}
