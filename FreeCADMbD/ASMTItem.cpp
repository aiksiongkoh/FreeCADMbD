/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTItem.h"
#include "ASMTSpatialContainer.h"
#include "ASMTAssembly.h"
#include "Constant.h"
#include <algorithm>
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTItem> ASMTItem::With()
{
    auto inst = std::make_shared<ASMTItem>();
    inst->initialize();
    return inst;
}

void ASMTItem::initialize()
{
    //Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::initializeGlobally()
{
    //Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::initializeLocally()
{
    //Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

ASMTAssembly* ASMTItem::root()
{
    return owner->root();
}

ASMTSpatialContainer* ASMTItem::partOrAssembly()
{
    return owner->partOrAssembly();
}

ASMTPart* ASMTItem::part()
{
    return owner->part();
}

void ASMTItem::noop()
{
    //No Operations
}

std::string ASMTItem::classname()
{
    std::string str = typeid(*this).name();
    auto answer = str.substr(11, str.size() - 11);
    return answer;
}

void ASMTItem::setName(const std::string& str)
{
    name = str;
}

void ASMTItem::parseASMT(std::vector<std::string>&)
{
    throw SimulationStoppingError("To be implemented.");
}

std::string ASMTItem::popOffTop(std::vector<std::string>& args)
{
    auto str = args.at(0);    //Must copy string
    args.erase(args.begin());
    return str;
}

std::string ASMTItem::readStringNoSpacesOffTop(std::vector<std::string>& args)
{
    //Return top string without whitespaces.
    std::string str = popOffTop(args);
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

FRowDsptr ASMTItem::readRowOfDoubles(const std::string& line)
{
    std::istringstream iss(line);
    auto readRowOfDoubles = FullRow<double>::With();
    double d;
    while (iss >> d) {
        readRowOfDoubles->push_back(d);
    }
    return readRowOfDoubles;
}

FRowDsptr ASMTItem::readRowOfDoublesOffTop(std::vector<std::string>& lines)
{
    auto str = popOffTop(lines);
    return readRowOfDoubles(str);
}

FColDsptr ASMTItem::readColumnOfDoubles(const std::string& line)
{
    std::istringstream iss(line);
    auto readColumnOfDoubles = FullColumn<double>::With();
    double d;
    while (iss >> d) {
        readColumnOfDoubles->push_back(d);
    }
    return readColumnOfDoubles;
}

FColDsptr ASMTItem::readColumnOfDoublesOffTop(std::vector<std::string>& lines)
{
    auto str = popOffTop(lines);
    return readColumnOfDoubles(str);
}

double ASMTItem::readDouble(const std::string& line)
{
    std::istringstream iss(line);
    double d;
    iss >> d;
    return d;
}

int ASMTItem::readInt(const std::string& line)
{
    std::istringstream iss(line);
    int i;
    iss >> i;
    return i;
}

size_t ASMTItem::readSize_t(const std::string& line)
{
    std::istringstream iss(line);
    size_t i;
    iss >> i;
    return i;
}

bool ASMTItem::readBool(const std::string& line)
{
    if (line.find("true") != std::string::npos)
    {
        return true;
    }
    else     if (line.find("false") != std::string::npos)
    {
        return false;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
        return false;
    }
}

std::string ASMTItem::readString(const std::string& line)
{
    //Read string without whitespaces.
    std::string str = line;
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

void ASMTItem::readName(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Name");
    name = readStringNoSpacesOffTop(lines);
}

std::string ASMTItem::fullName(const std::string& partialName)
{
    std::string longerName = "/" + name + partialName;
    if (owner == nullptr) {
        return longerName;
    }
    else {
        return owner->fullName(longerName);
    }
}

void ASMTItem::readDoublesInto(std::string& str, std::string label, FRowDsptr& row)
{
    auto pos = str.find(label);
    assert(pos != std::string::npos);
    str.erase(0, pos + label.length());
    row = readRowOfDoubles(str);
}

void ASMTItem::deleteMbD()
{
    mbdObject = nullptr;
}

void ASMTItem::createMbD()
{
    noop();
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::updateFromMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<StateData> ASMTItem::dataFromMbD()
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<StateData>();
}

void ASMTItem::compareResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Units> ASMTItem::asmtUnits()
{
    return root()->asmtUnits;
}

std::shared_ptr<Units> ASMTItem::mbdUnits()
{
    return mbdSys()->mbdUnits;
}

std::shared_ptr<System> ASMTItem::mbdSys()
{
    return root()->mbdSystem;
}

std::shared_ptr<Constant> ASMTItem::sptrConstant(double value)
{
    return Constant::With(value);
}

void ASMTItem::storeOnLevel(std::ofstream&, size_t)
{
    noop();
}

void ASMTItem::storeOnLevelTabs(std::ofstream& os, size_t level)
{
    for (size_t i = 0; i < level; i++)
    {
        os << '\t';
    }
}

void ASMTItem::storeOnLevelString(std::ofstream& os, size_t level, std::string str)
{
    storeOnLevelTabs(os, level);
    os << str << std::endl;
}

void ASMTItem::storeOnLevelDouble(std::ofstream& os, size_t level, double value)
{
    storeOnLevelTabs(os, level);
    os << value << std::endl;
}

void ASMTItem::storeOnLevelInt(std::ofstream& os, size_t level, int i)
{
    storeOnLevelTabs(os, level);
    os << i << std::endl;
}

void ASMTItem::storeOnLevelSize_t(std::ofstream& os, size_t level, size_t i)
{
    storeOnLevelTabs(os, level);
    os << i << std::endl;
}

void ASMTItem::storeOnLevelBool(std::ofstream& os, size_t level, bool value)
{
    storeOnLevelTabs(os, level);
    if (value) {
        os << "true" << std::endl;
    }
    else {
        os << "false" << std::endl;
    }
}

void ASMTItem::storeOnLevelArray(std::ofstream& os, size_t level, std::vector<double> array)
{
    storeOnLevelTabs(os, level);
    for (size_t i = 0; i < array.size(); i++)
    {
        os << array[i] << '\t';
    }
    os << std::endl;
}

void ASMTItem::storeOnLevelName(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "Name");
    storeOnLevelString(os, level + 1, name);
}

void ASMTItem::storeOnTimeSeries(std::ofstream&)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::logString(const std::string& str)
{
    std::cout << str << std::endl;
}
