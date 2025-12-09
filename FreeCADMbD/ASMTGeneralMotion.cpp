/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTGeneralMotion.h"
#include "ASMTAssembly.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "EulerAngles.h"
#include "FullMotion.h"
#include "ASMTTime.h"

using namespace MbD;

std::shared_ptr<ASMTGeneralMotion> ASMTGeneralMotion::With()
{
    auto inst = std::make_shared<ASMTGeneralMotion>();
    inst->initialize();
    return inst;
}

void ASMTGeneralMotion::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    readMarkerI(lines);
    readMarkerJ(lines);
    readrIJI(lines);
    readangIJJ(lines);
    readRotationOrder(lines);
}

void ASMTGeneralMotion::readrIJI(std::vector<std::string>& lines)
{
    rIJI = std::make_shared<FullColumn<std::string>>(3);

    assert(readStringNoSpacesOffTop(lines) == "rIJI1");
    rIJI->at(0) = readStringNoSpacesOffTop(lines);
    assert(readStringNoSpacesOffTop(lines) == "rIJI2");
    rIJI->at(1) = readStringNoSpacesOffTop(lines);
    assert(readStringNoSpacesOffTop(lines) == "rIJI3");
    rIJI->at(2) = readStringNoSpacesOffTop(lines);
}

void ASMTGeneralMotion::readangIJJ(std::vector<std::string>& lines)
{
    angIJJ = std::make_shared<FullColumn<std::string>>(3);

    assert(readStringNoSpacesOffTop(lines) == "angIJJ1");
    angIJJ->at(0) = readStringNoSpacesOffTop(lines);
    assert(readStringNoSpacesOffTop(lines) == "angIJJ2");
    angIJJ->at(1) = readStringNoSpacesOffTop(lines);
    assert(readStringNoSpacesOffTop(lines) == "angIJJ3");
    angIJJ->at(2) = readStringNoSpacesOffTop(lines);
}

void ASMTGeneralMotion::readRotationOrder(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RotationOrder");
    std::istringstream iss(lines[0]);
    rotationOrder = std::make_shared<std::vector<size_t>>();
    size_t i;
    while (iss >> i) {
        rotationOrder->push_back(i);
    }
    lines.erase(lines.begin());
}

std::shared_ptr<ConstraintSet> ASMTGeneralMotion::mbdClassNew()
{
    return FullMotion::With();
}

void ASMTGeneralMotion::createMbD()
{
    ASMTMotion::createMbD();
    auto parser = std::make_shared<SymbolicParser>();
    parser->owner = this;
    auto geoTime = owner->root()->geoTime();
    parser->variables->insert(std::make_pair("time", geoTime));
    std::shared_ptr< BasicUserFunction> userFunc;
    auto fullMotion = std::static_pointer_cast<FullMotion>(mbdObject);

    //rIJI
    userFunc = std::make_shared<BasicUserFunction>(rIJI->at(0), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoX = parser->stack->top();
    geoX = Symbolic::times(geoX, sptrConstant(asmtUnits()->length));
    geoX->createMbD();
    auto xBlk = geoX->simplified(geoX);

    userFunc = std::make_shared<BasicUserFunction>(rIJI->at(1), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoY = parser->stack->top();
    geoY = Symbolic::times(geoY, sptrConstant(asmtUnits()->length));
    geoY->createMbD();
    auto yBlk = geoY->simplified(geoY);

    userFunc = std::make_shared<BasicUserFunction>(rIJI->at(2), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoZ = parser->stack->top();
    geoZ = Symbolic::times(geoZ, sptrConstant(asmtUnits()->length));
    geoZ->createMbD();
    auto zBlk = geoZ->simplified(geoZ);

    auto xyzBlkList = std::initializer_list<Symsptr>{ xBlk, yBlk, zBlk };
    fullMotion->frIJI = std::make_shared<FullColumn<Symsptr>>(xyzBlkList);

    //angIJJ
    userFunc = std::make_shared<BasicUserFunction>(angIJJ->at(0), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoPhi = parser->stack->top();
    geoPhi = Symbolic::times(geoPhi, sptrConstant(asmtUnits()->angle));
    geoPhi->createMbD();
    auto phiBlk = geoPhi->simplified(geoPhi);

    userFunc = std::make_shared<BasicUserFunction>(angIJJ->at(1), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoThe = parser->stack->top();
    geoThe = Symbolic::times(geoThe, sptrConstant(asmtUnits()->angle));
    geoThe->createMbD();
    auto theBlk = geoThe->simplified(geoThe);

    userFunc = std::make_shared<BasicUserFunction>(angIJJ->at(2), 1.0);
    parser->parseUserFunction(userFunc);
    auto& geoPsi = parser->stack->top();
    geoPsi = Symbolic::times(geoPsi, sptrConstant(asmtUnits()->angle));
    geoPsi->createMbD();
    auto psiBlk = geoPsi->simplified(geoPsi);

    auto xyzRotBlkList = std::initializer_list<Symsptr>{ phiBlk, theBlk, psiBlk };
    auto fangIJJ = std::make_shared<EulerAngles<Symsptr>>(xyzRotBlkList);
    fangIJJ->rotOrder = rotationOrder;
    fullMotion->fangIJJ = fangIJJ;
}

void ASMTGeneralMotion::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "GeneralMotion");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTGeneralMotion::storeOnTimeSeries(std::ofstream& os)
{
    os << "GeneralMotionSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}
