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
    if (infxs == nullptr || infxs->empty())
        return;
    auto lambda = [&](std::string name, std::shared_ptr<std::vector<FColDsptr>> cols, size_t icomp, FRowDsptr invals, size_t i, size_t nSig, double tol)
    {
        auto val = cols->at(i)->at(icomp);
        auto inval = invals->at(i);
        auto tol2 = tol / 10.0;
        if (std::abs(val) < tol2 && std::abs(inval) < tol2)
            return;
        auto ratio = val / inval;
        auto relDiff = std::abs(ratio) - 1.0;
        if (ratio < 0.0)
        {
            std::cout << "                    Sign Error ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << std::endl;
        }
        else if (std::abs(relDiff) >= std::pow(10, -int(nSig)))
        {
            std::cout << "                    ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << std::endl;
        }
    };

    auto mbdUnts = mbdUnits();
    size_t nDigit = 3;
    auto factor = std::pow(10, -int(nDigit));
    auto forceTol = mbdUnts->force * factor;
    auto torqueTol = mbdUnts->torque * factor;
    auto i = cFIO->size() - 1;
    // Force
    lambda("FIOx", cFIO, 0, infxs, i, nDigit, forceTol);
    lambda("FIOy", cFIO, 1, infys, i, nDigit, forceTol);
    lambda("FIOz", cFIO, 2, infzs, i, nDigit, forceTol);
    // Torque
    lambda("TIOx", cTIO, 0, intxs, i, nDigit, torqueTol);
    lambda("TIOy", cTIO, 1, intys, i, nDigit, torqueTol);
    lambda("TIOz", cTIO, 2, intzs, i, nDigit, torqueTol);
}

void ASMTForceTorque::compareResults2(AnalysisType type)
{
    if (dataSeriesIn == nullptr || dataSeriesIn->empty())
        return;
    auto lambda = [&](std::string name, size_t i, FColDsptr col, FColDsptr incol, size_t nSig, double tol)
    {
        auto val = col->at(i);
        auto inval = incol->at(i);
        auto tol2 = tol / 10.0;
        if (std::abs(val) < tol2 && std::abs(inval) < tol2)
            return;
        auto ratio = val / inval;
        auto relDiff = std::abs(ratio) - 1.0;
        if (ratio < 0.0)
        {
            std::cout << "                    Sign Error ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << std::endl;
        }
        else if (std::abs(relDiff) >= std::pow(10, -int(nSig)))
        {
            std::cout << "                    ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << std::endl;
        }
    };

    auto mbdUnts = mbdUnits();
    size_t nDigit = 3;
    auto factor = std::pow(10, -int(nDigit));
    auto forceTol = mbdUnts->force * factor;
    auto torqueTol = mbdUnts->torque * factor;
    auto i = dataSeries->size() - 1;
    auto forceTorqueData = std::dynamic_pointer_cast<ForceTorqueData>(dataSeries->at(i));
    auto forceTorqueDataIn = std::dynamic_pointer_cast<ForceTorqueData>(dataSeriesIn->at(i));
    auto aFIeO = forceTorqueData->aFIO;
    auto inFIeO = forceTorqueDataIn->aFIO;
    // Force
    lambda("FIOx", 0, aFIeO, inFIeO, nDigit, forceTol);
    lambda("FIOy", 1, aFIeO, inFIeO, nDigit, forceTol);
    lambda("FIOz", 2, aFIeO, inFIeO, nDigit, forceTol);
    // Torque
    auto aTIeO = forceTorqueData->aTIO;
    auto inTIeO = forceTorqueDataIn->aTIO;
    lambda("TIOx", 0, aTIeO, inTIeO, nDigit, torqueTol);
    lambda("TIOy", 1, aTIeO, inTIeO, nDigit, torqueTol);
    lambda("TIOz", 2, aTIeO, inTIeO, nDigit, torqueTol);
}

void ASMTForceTorque::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTForceTorque::readForceTorqueSeries(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    std::string substr = "ForceTorqueSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0u, pos + substr.length()); // Use 0u to ensure unsigned type for erase
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());
    
    auto infxs2 = readSeriesOf(lines, "FXonI");
    auto infys2 = readSeriesOf(lines, "FYonI");
    auto infzs2 = readSeriesOf(lines, "FZonI");
    auto intxs2 = readSeriesOf(lines, "TXonI");
    auto intys2 = readSeriesOf(lines, "TYonI");
    auto intzs2 = readSeriesOf(lines, "TZonI");

    for (size_t i = 0; i < infxs2->size(); ++i)
    {
        auto data = ForceTorqueData::With();
        auto lambda = [&](FRowDsptr rowx, FRowDsptr rowy, FRowDsptr rowz) -> FColDsptr
        {
            auto col = FullColumn<double>::With(3);
            col->at(0) = rowx->at(i);
            col->at(1) = rowy->at(i);
            col->at(2) = rowz->at(i);
            return col;
        };
        data->aFIO = lambda(infxs2, infys2, infzs2);
        data->aTIO = lambda(intxs2, intys2, intzs2);
        dataSeriesIn->push_back(data);
    }

    // readFXonIs(lines);
    // readFYonIs(lines);
    // readFZonIs(lines);
    // readTXonIs(lines);
    // readTYonIs(lines);
    // readTZonIs(lines);
}

void ASMTForceTorque::storeOnLevel(std::ofstream &os, size_t level)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTForceTorque::storeOnTimeSeries(std::ofstream &os)
{
    std::string label = typeid(*this).name();
    label = label.substr(15, label.size() - 15);
    os << label << "Series\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

void ASMTForceTorque::createMbD()
{
    // Do nothing.
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
    auto aForTor = std::static_pointer_cast<ForceTorqueIJ>(mbdObject);
    auto answer = ForceTorqueData::With();
    answer->aFIO = aForTor->aFIeO->times(mbdUnts->force);
    answer->aTIO = aForTor->aTIeO->times(mbdUnts->torque);
    return answer;
}
