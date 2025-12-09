/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTLimit.h"
#include "ASMTAssembly.h"
#include "ASMTJoint.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "LimitIJ.h"

using namespace MbD;

void ASMTLimit::initMarkers()
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

void ASMTLimit::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "MotionJoint");
    storeOnLevelString(os, level + 2, motionJoint);
    storeOnLevelString(os, level + 1, "Limit");
    storeOnLevelString(os, level + 2, limit);
    storeOnLevelString(os, level + 1, "Type");
    storeOnLevelString(os, level + 2, type);
    storeOnLevelString(os, level + 1, "Tol");
    storeOnLevelString(os, level + 2, tol);
}

void ASMTLimit::readMotionJoint(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MotionJoint");
    motionJoint = readStringNoSpacesOffTop(lines);
}

void ASMTLimit::readLimit(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Limit");
    limit = readStringNoSpacesOffTop(lines);
}

void ASMTLimit::readType(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Type");
    type = readStringNoSpacesOffTop(lines);
}

void ASMTLimit::readTol(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Tol");
    tol = readStringNoSpacesOffTop(lines);
}

void ASMTLimit::parseASMT(std::vector<std::string>& lines)
{
    ASMTConstraintSet::parseASMT(lines);
    readMotionJoint(lines);
    readLimit(lines);
    readType(lines);
    readTol(lines);
}

void ASMTLimit::createMbD()
{
    ASMTConstraintSet::createMbD();
    auto limitIJ = std::static_pointer_cast<LimitIJ>(mbdObject);
    mbdSys()->addLimit(limitIJ);
    //
    auto parser = std::make_shared<SymbolicParser>();
    parser->owner = this;
    std::shared_ptr<BasicUserFunction> userFunc;
    //
    userFunc = std::make_shared<BasicUserFunction>(limit, 1.0);
    parser->parseUserFunction(userFunc);
    auto& geolimit = parser->stack->top();
    geolimit = Symbolic::times(geolimit, sptrConstant(1.0 / mbdUnits()->angle));
    geolimit->createMbD();
    geolimit = geolimit->simplified(geolimit);
    limitIJ->limit = geolimit->getValue();
    //
    limitIJ->type = type;
    //
    userFunc = std::make_shared<BasicUserFunction>(tol, 1.0);
    parser->parseUserFunction(userFunc);
    auto& geotol = parser->stack->top();
    geotol = Symbolic::times(geotol, sptrConstant(1.0 / mbdUnits()->angle));
    geotol->createMbD();
    geotol = geotol->simplified(geotol);
    limitIJ->tol = geotol->getValue();
}

void ASMTLimit::setmotionJoint(const std::string& _motionJoint)
{
    motionJoint = _motionJoint;
}

void ASMTLimit::settype(const std::string& _type)
{
    type = _type;
}

void ASMTLimit::setlimit(const std::string& _limit)
{
    limit = _limit;
}

void ASMTLimit::settol(const std::string& _tol)
{
    tol = _tol;
}
