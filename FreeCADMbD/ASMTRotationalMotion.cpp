/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTRotationalMotion.h"
#include "ASMTAssembly.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "ASMTJoint.h"
#include "ASMTTime.h"

using namespace MbD;

std::shared_ptr<ASMTRotationalMotion> ASMTRotationalMotion::With()
{
    auto inst = std::make_shared<ASMTRotationalMotion>();
    inst->initialize();
    return inst;
}

void ASMTRotationalMotion::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    if (lines[0].find("MarkerI") != std::string::npos) {
        readMarkerI(lines);
        readMarkerJ(lines);
    }
    readMotionJoint(lines);
    readRotationZ(lines);
}

void ASMTRotationalMotion::readMotionJoint(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MotionJoint");
    motionJoint = readStringNoSpacesOffTop(lines);
}

void ASMTRotationalMotion::readRotationZ(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RotationZ");
    rotationZ = readStringNoSpacesOffTop(lines);
}

void ASMTRotationalMotion::createMbD()
{
    ASMTMotion::createMbD();
    auto parser = std::make_shared<SymbolicParser>();
    parser->owner = this;
    auto geoTime = owner->root()->geoTime();
    parser->variables->insert(std::make_pair("time", geoTime));
    auto userFunc = std::make_shared<BasicUserFunction>(rotationZ, 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoPhi = parser->stack->top();
    //std::cout << *geoPhi << std::endl;
    geoPhi = Symbolic::times(geoPhi, sptrConstant(asmtUnits()->angle));
    geoPhi->createMbD();
    //std::cout << *geoPhi << std::endl;
    auto simple = geoPhi->simplified(geoPhi);
    //std::cout << *simple << std::endl;
    std::static_pointer_cast<ZRotation>(mbdObject)->phiBlk = simple;
}

std::shared_ptr<ConstraintSet> ASMTRotationalMotion::mbdClassNew()
{
    return ZRotation::With();
}

void ASMTRotationalMotion::setMotionJoint(std::string motionJoint)
{
    this->motionJoint = motionJoint;
}

void ASMTRotationalMotion::setRotationZ(std::string rotZ)
{
    rotationZ = rotZ;
}

void ASMTRotationalMotion::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RotationalMotion");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "MotionJoint");
    storeOnLevelString(os, level + 2, motionJoint);
    storeOnLevelString(os, level + 1, "RotationZ");
    storeOnLevelString(os, level + 2, rotationZ);
}

void ASMTRotationalMotion::storeOnTimeSeries(std::ofstream& os)
{
    os << "RotationalMotionSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
