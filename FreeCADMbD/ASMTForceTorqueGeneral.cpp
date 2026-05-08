/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorqueGeneral.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "ASMTTime.h"
#include "ForceTorqueGeneral.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"
#include "ForceTorqueData.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueGeneral> ASMTForceTorqueGeneral::With()
{
    auto inst = std::make_shared<ASMTForceTorqueGeneral>();
    inst->initialize();
    return inst;
}

void ASMTForceTorqueGeneral::initialize()
{
    ASMTForceTorque::initialize();
    markerKSign = "I";
    aFIeKe = FullColumn<std::string>::With(3);
    aTIeKe = FullColumn<std::string>::With(3);
}

void ASMTForceTorqueGeneral::storeOnLevel(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "GeneralForceTorque");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "FxOnI");
    storeOnLevelString(os, level + 2, aFIeKe->at(0));
    storeOnLevelString(os, level + 1, "FyOnI");
    storeOnLevelString(os, level + 2, aFIeKe->at(1));
    storeOnLevelString(os, level + 1, "FzOnI");
    storeOnLevelString(os, level + 2, aFIeKe->at(2));
    storeOnLevelString(os, level + 1, "FxOnI");
    storeOnLevelString(os, level + 2, aTIeKe->at(0));
    storeOnLevelString(os, level + 1, "TyOnI");
    storeOnLevelString(os, level + 2, aTIeKe->at(1));
    storeOnLevelString(os, level + 1, "TzOnI");
    storeOnLevelString(os, level + 2, aTIeKe->at(2));
}

void ASMTForceTorqueGeneral::storeOnTimeSeries(std::ofstream &os)
{
    cFIO->reserve(dataSeries->size());
    for (const auto &data : *dataSeries)
    {
        cFIO->push_back(std::dynamic_pointer_cast<ForceTorqueData>(data)->aFIO);
    }
    cTIO->reserve(dataSeries->size());
    for (const auto &data : *dataSeries)
    {
        cTIO->push_back(std::dynamic_pointer_cast<ForceTorqueData>(data)->aTIO);
    }

    auto dst = std::make_shared<std::vector<std::shared_ptr<ForceTorqueData>>>();
    dst->reserve(dataSeries->size());

    std::transform(dataSeries->begin(), dataSeries->end(), std::back_inserter(*dst),
                   [](const std::shared_ptr<StateData> &s)
                   {
                       return std::dynamic_pointer_cast<ForceTorqueData>(s);
                   });

    os << "GeneralForceTorqueSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

void ASMTForceTorqueGeneral::createMbD()
{
    ASMTForceTorque::createMbD();
    auto eFrmI = std::static_pointer_cast<EndFrame>(markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFrame>(markerJ->mbdObject);
    assert(eFrmJ->has_qX());
    std::shared_ptr<ForceTorqueGeneral> forceTorqueGeneral;
    if (markerKSign == "O")
    {
        forceTorqueGeneral = ForceTorqueGeneral::With(eFrmI, eFrmJ, nullptr);
    }
    else
    {
        std::shared_ptr<EndFrame> efrmK;
        if (markerKSign == "J")
        {
            efrmK = eFrmJ;
        }
        else
        {
            efrmK = eFrmI;
        }
        forceTorqueGeneral = ForceTorqueGeneral::With(eFrmI, eFrmJ, efrmK);
    }
    forceTorqueGeneral->name = fullName("");
    auto aFIeKeFunc = FullColumn<Symsptr>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        auto aFIeKei = aFIeKe->at(i);
        if (aFIeKei != "")
        {
            auto parser = functionParser();
            parser->owner = this;
            auto geoTime = owner->root()->geoTime();
            parser->variables->insert(std::make_pair("time", geoTime));
            auto userFunc = std::make_shared<BasicUserFunction>(aFIeKei, 1.0);
            parser->parseUserFunction(userFunc);
            auto aFIeKeiFunc = parser->stack->top();
            aFIeKeiFunc = Symbolic::times(aFIeKeiFunc, sptrConstant(asmtUnits()->force));
            aFIeKeiFunc->createMbD();
            auto simple = aFIeKeiFunc->simplified(aFIeKeiFunc);
            aFIeKeFunc->atiput(i, simple);
        }
    }
    forceTorqueGeneral->setForceFunctions(aFIeKeFunc);
    auto aTIeKeFunc = FullColumn<Symsptr>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        auto aTIeKei = aTIeKe->at(i);
        if (aTIeKei != "")
        {
            auto parser = functionParser();
            auto userFunc = std::make_shared<BasicUserFunction>(aTIeKei, 1.0);
            parser->parseUserFunction(userFunc);
            auto aTIeKeiFunc = parser->stack->top();
            aTIeKeiFunc = Symbolic::times(aTIeKeiFunc, sptrConstant(asmtUnits()->torque));
            aTIeKeiFunc->createMbD();
            auto simple = aTIeKeiFunc->simplified(aTIeKeiFunc);
            aTIeKeFunc->atiput(i, simple);
        }
    }
    forceTorqueGeneral->setTorqueFunctions(aTIeKeFunc);
    mbdObject = forceTorqueGeneral;
    mbdSys()->addForceTorque(forceTorqueGeneral);
    forceTorqueGeneral->initializeLocally();
}

void ASMTForceTorqueGeneral::parseASMT(std::vector<std::string> &lines)
{
    ASMTForceTorque::parseASMT(lines);
    readFxOnI(lines);
    readFyOnI(lines);
    readFzOnI(lines);
    readTxOnI(lines);
    readTyOnI(lines);
    readTzOnI(lines);
    readMarkerKSign(lines);
}

void ASMTForceTorqueGeneral::readFxOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "FxOnI");
    aFIeKe->atiput(0, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readFyOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "FyOnI");
    aFIeKe->atiput(1, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readFzOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "FzOnI");
    aFIeKe->atiput(2, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTxOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "TxOnI");
    aTIeKe->atiput(0, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTyOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "TyOnI");
    aTIeKe->atiput(1, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTzOnI(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "TzOnI");
    aTIeKe->atiput(2, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readMarkerKSign(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "MarkerK");
    markerKSign = readStringNoSpacesOffTop(lines);
}
