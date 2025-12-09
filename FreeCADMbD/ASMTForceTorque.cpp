/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorque.h"
#include "ASMTAssembly.h"
#include "ForceFunctionParser.h"
#include "ForceTorqueIJ.h"
#include "ForceTorqueData.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorque> ASMTForceTorque::With()
{
    auto inst = std::make_shared<ASMTForceTorque>();
    inst->initialize();
    return inst;
}

void ASMTForceTorque::updateFromMbD()
{
    auto data = dataFromMbD();
    dataSeries->push_back(data);
}

void ASMTForceTorque::compareResults(AnalysisType)
{
    if (infxs == nullptr || infxs->empty()) return;
    auto mbdUnts = mbdUnits();
    //auto factor = 1.0e-6;
    //auto forceTol = mbdUnts->force * factor;
    //auto torqueTol = mbdUnts->torque * factor;
    //auto i = fxs->size() - 1;
    //assert(Numeric::equaltol(fxs->at(i), infxs->at(i), forceTol));
    //assert(Numeric::equaltol(fys->at(i), infys->at(i), forceTol));
    //assert(Numeric::equaltol(fzs->at(i), infzs->at(i), forceTol));
    //assert(Numeric::equaltol(txs->at(i), intxs->at(i), torqueTol));
    //assert(Numeric::equaltol(tys->at(i), intys->at(i), torqueTol));
    //assert(Numeric::equaltol(tzs->at(i), intzs->at(i), torqueTol));
}

void ASMTForceTorque::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTForceTorque::readForceTorqueSeries(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    std::string substr = "ForceTorqueSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());
    readFXonIs(lines);
    readFYonIs(lines);
    readFZonIs(lines);
    readTXonIs(lines);
    readTYonIs(lines);
    readTZonIs(lines);
}

void ASMTForceTorque::storeOnLevel(std::ofstream& os, size_t level)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTForceTorque::storeOnTimeSeries(std::ofstream& os)
{
    std::string label = typeid(*this).name();
    label = label.substr(15, label.size() - 15);
    os << label << "Series\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

void ASMTForceTorque::createMbD()
{
    //Do nothing.
}

std::shared_ptr<ForceFunctionParser> ASMTForceTorque::functionParser()
{
    auto parser = ForceFunctionParser::With();
    parser->owner = this;
    parser->initVariables();
    parser->initgeoIJs();
    return parser;

}

bool ASMTForceTorque::isForceTorque()
{
    return true;
}

std::shared_ptr<StateData> ASMTForceTorque::dataFromMbD()
{
    auto mbdUnts = mbdUnits();
    auto mbdItem = std::static_pointer_cast<ForceTorqueIJ>(mbdObject);
    auto answer = ForceTorqueData::With();
    answer->aFIO = mbdItem->aFX()->times(mbdUnts->force);
    answer->aTIO = mbdItem->aTX()->times(mbdUnts->torque);
    return answer;
}
