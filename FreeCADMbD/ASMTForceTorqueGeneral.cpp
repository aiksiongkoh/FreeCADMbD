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
#include "ForceTorqueGeneral.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueGeneral> ASMTForceTorqueGeneral::With()
{
    auto inst = std::make_shared<ASMTForceTorqueGeneral>();
    inst->initialize();
    return inst;
}

void ASMTForceTorqueGeneral::initialize()
{
    markerKSign = "I";
    aFIeKe = FullColumn<std::string>::With(3);
    aTIeKe = FullColumn<std::string>::With(3);
}

void ASMTForceTorqueGeneral::storeOnLevel(std::ofstream& os, size_t level)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTForceTorqueGeneral::storeOnTimeSeries(std::ofstream& os)
{
    os << "GeneralForceTorqueSeries\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

void ASMTForceTorqueGeneral::createMbD()
{
        ASMTForceTorque::createMbD();
        auto eFrmI = std::static_pointer_cast<EndFrameqc>(markerI->mbdObject);
        auto eFrmJ = std::static_pointer_cast<EndFrameqc>(markerJ->mbdObject);
        std::shared_ptr<ForceTorqueGeneral> forceTorqueGeneral;
        if (markerKSign == "O") {
            forceTorqueGeneral = ForceTorqueGeneral::OnFrmIandFrmJ(eFrmI, eFrmJ);
        }
        else {
            std::shared_ptr<EndFrameqc> efrmK;
            if (markerKSign == "J") {
                efrmK = eFrmJ;
            }
            else {
                efrmK = eFrmI;
            }
            forceTorqueGeneral = ForceTorqueGeneral::OnFrmIandFrmJwrtFrmK(eFrmI, eFrmJ, efrmK);
        }
        forceTorqueGeneral->name = fullName("");        
        auto aFIeKeFunc = FullColumn<Symsptr>::With(3);
        for (size_t i = 0; i < 3; i++)
        {
            auto aFIeKei = aFIeKe->at(i);
            if (aFIeKei != "") {
                auto parser = functionParser();
                auto userFunc = std::make_shared<BasicUserFunction>(aFIeKei, 1.0);
                parser->parseUserFunction(userFunc);
                auto aFIeKeiFunc = parser->stack->top();
                aFIeKeiFunc = Symbolic::times(aFIeKeiFunc, sptrConstant(asmtUnits()->force));
                aFIeKeiFunc->createMbD();
                auto simple = aFIeKeiFunc->simplified(aFIeKeiFunc);
                aFIeKeFunc->atiput(i, simple);
            }
        }
        forceTorqueGeneral->forceFunctions(aFIeKeFunc);
        auto aTIeKeFunc = FullColumn<Symsptr>::With(3);
        for (size_t i = 0; i < 3; i++)
        {
            auto aTIeKei = aTIeKe->at(i);
            if (aTIeKei != "") {
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
        forceTorqueGeneral->torqueFunctions(aTIeKeFunc);
        mbdObject = forceTorqueGeneral;
        mbdSys()->addForceTorque(forceTorqueGeneral);
        forceTorqueGeneral->initializeLocally();
}

void ASMTForceTorqueGeneral::parseASMT(std::vector<std::string>& lines)
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

void ASMTForceTorqueGeneral::readFxOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "FxOnI");
    aFIeKe->atiput(0, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readFyOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "FyOnI");
    aFIeKe->atiput(1, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readFzOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "FzOnI");
    aFIeKe->atiput(2, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTxOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "TxOnI");
    aTIeKe->atiput(0, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTyOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "TyOnI");
    aTIeKe->atiput(1, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readTzOnI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "TzOnI");
    aTIeKe->atiput(2, popOffTop(lines));
}

void ASMTForceTorqueGeneral::readMarkerKSign(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MarkerK");
    markerKSign = readStringNoSpacesOffTop(lines);
}
