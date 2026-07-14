/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorqueInLine.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "ForceTorqueInLine.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueInLine> ASMTForceTorqueInLine::With()
{
    auto inst = std::make_shared<ASMTForceTorqueInLine>();
    inst->initialize();
    return inst;
}

void ASMTForceTorqueInLine::parseASMT(std::vector<std::string>& lines)
{
    ASMTForceTorque::parseASMT(lines);
    readTension(lines);
    readTwist(lines);
}

void ASMTForceTorqueInLine::readTension(std::vector<std::string>& lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "tension");
    tensionFunc = readStringTrimmedOffTop(lines);
}

void ASMTForceTorqueInLine::readTwist(std::vector<std::string>& lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "twist");
    twistFunc = readStringTrimmedOffTop(lines);
}

void ASMTForceTorqueInLine::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "InLineForceTorque");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "tension");
    storeOnLevelString(os, level + 2, tensionFunc);
    storeOnLevelString(os, level + 1, "twist");
    storeOnLevelString(os, level + 2, twistFunc);
}

void ASMTForceTorqueInLine::storeOnTimeSeries(std::ofstream& os)
{
    os << "InLineForceTorqueSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

void ASMTForceTorqueInLine::createMbD()
{
    ASMTForceTorque::createMbD();
    auto mrkI = std::static_pointer_cast<EndFrame>(markerI->mbdObject);
    auto mrkJ = std::static_pointer_cast<EndFrame>(markerJ->mbdObject);
    auto mbdForceTorqueInLine = ForceTorqueInLine::With(mrkI, mrkJ);
    mbdForceTorqueInLine->name = fullName("");
    Symsptr tension, twist;

    auto parser = functionParser();
    auto userFunc = std::make_shared<BasicUserFunction>(tensionFunc, 1.0);
    parser->parseUserFunction(userFunc);
    tension = parser->stack->top();
    tension = Symbolic::times(tension, sptrConstant(asmtUnits()->force));
    tension->createMbD();
    //std::cout << *tension << std::endl;
    auto simple = tension->simplified(tension);
    //std::cout << *simple << std::endl;
    mbdForceTorqueInLine->setTension(simple);

    parser = functionParser();
    userFunc = std::make_shared<BasicUserFunction>(twistFunc, 1.0);
    parser->parseUserFunction(userFunc);
    twist = parser->stack->top();
    twist = Symbolic::times(twist, sptrConstant(asmtUnits()->torque));
    twist->createMbD();
    //std::cout << *twist << std::endl;
    simple = twist->simplified(twist);
    //std::cout << *simple << std::endl;
    mbdForceTorqueInLine->setTwist(simple);
    mbdObject = mbdForceTorqueInLine;
    mbdSys()->addForceTorque(mbdForceTorqueInLine);
}

std::string ASMTForceTorqueInLine::reportComparisonWith(std::shared_ptr<ASMTItem> other)
{
    auto report = ASMTItemIJ::reportComparisonWith(other);
    if (!report.empty()) {
        return report;
    }
    auto otherForceTorque = std::dynamic_pointer_cast<ASMTForceTorqueInLine>(other);
    if (!otherForceTorque) {
        return fullName("") + " comparison item is not an ASMTForceTorqueInLine.\n";
    }
    if (tensionFunc != otherForceTorque->tensionFunc) {
        return fullName("") + " tension " + tensionFunc + " != " + otherForceTorque->tensionFunc + "\n";
    }
    if (twistFunc != otherForceTorque->twistFunc) {
        return fullName("") + " twist " + twistFunc + " != " + otherForceTorque->twistFunc + "\n";
    }
    return std::string{};
}
