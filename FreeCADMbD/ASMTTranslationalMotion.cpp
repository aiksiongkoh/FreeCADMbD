/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTTranslationalMotion.h"
#include "ASMTAssembly.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "ASMTJoint.h"
#include "ZTranslation.h"
#include "ASMTTime.h"

using namespace MbD;

std::shared_ptr<ASMTTranslationalMotion> ASMTTranslationalMotion::With()
{
    auto inst = std::make_shared<ASMTTranslationalMotion>();
    inst->initialize();
    return inst;
}

void ASMTTranslationalMotion::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    if (lines[0].find("MarkerI") != std::string::npos) {
        readMarkerI(lines);
        readMarkerJ(lines);
    }
    readMotionJoint(lines);
    readTranslationZ(lines);
}

void ASMTTranslationalMotion::createMbD()
{
    ASMTMotion::createMbD();
    auto parser = SymbolicParser::With();
    parser->owner = this;
    auto geoTime = owner->root()->geoTime();
    parser->variables->insert(std::make_pair("time", geoTime));
    auto userFunc = std::make_shared<BasicUserFunction>(translationZ, 1.0);
    parser->parseUserFunction(userFunc);
    auto zIJ = parser->stack->top();
    zIJ = Symbolic::times(zIJ, sptrConstant(asmtUnits()->length));
    zIJ->createMbD();
    std::static_pointer_cast<ZTranslation>(mbdObject)->zBlk = zIJ->simplified(zIJ);
}

std::shared_ptr<ConstraintSet> ASMTTranslationalMotion::mbdClassNew()
{
    return ZTranslation::With();
}

void ASMTTranslationalMotion::readMotionJoint(std::vector<std::string>& lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "MotionJoint");
    motionJoint = readStringNoSpacesOffTop(lines);
}

void ASMTTranslationalMotion::readTranslationZ(std::vector<std::string>& lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "TranslationZ");
    translationZ = readStringTrimmedOffTop(lines);
}

void ASMTTranslationalMotion::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "TranslationalMotion");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "MotionJoint");
    storeOnLevelString(os, level + 2, motionJoint);
    storeOnLevelString(os, level + 1, "TranslationZ");
    storeOnLevelString(os, level + 2, translationZ);
}

void ASMTTranslationalMotion::storeOnTimeSeries(std::ofstream& os)
{
    os << "TranslationalMotionSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

std::string ASMTTranslationalMotion::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTItemIJ::reportComparisonWith(otherItem);
    if (!report.empty()) {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTTranslationalMotion>(otherItem);
    if (!other) {
        return fullName("") + " comparison item is not an ASMTTranslationalMotion.\n";
    }
    if (motionJoint != other->motionJoint) {
        return fullName("") + " motionJoint " + motionJoint + " != " + other->motionJoint + "\n";
    }
    if (translationZ != other->translationZ) {
        return fullName("") + " translationZ " + translationZ + " != " + other->translationZ + "\n";
    }
    return std::string{};
}
