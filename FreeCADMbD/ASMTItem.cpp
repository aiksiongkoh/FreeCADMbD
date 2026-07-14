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
    // Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::initializeGlobally()
{
    // Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::initializeLocally()
{
    // Subclass responsibility.
    throw SimulationStoppingError("To be implemented.");
}

ASMTAssembly *ASMTItem::root()
{
    return owner->root();
}

ASMTSpatialContainer *ASMTItem::partOrAssembly()
{
    return owner->partOrAssembly();
}

ASMTPart *ASMTItem::part()
{
    return owner->part();
}

void ASMTItem::noop()
{
    // No Operations
}

std::string ASMTItem::classname()
{
    const std::string &str = typeid(*this).name();
    auto answer = str.substr(11, str.size() - 11);
    return answer;
}

void ASMTItem::setName(const std::string &str)
{
    name = str;
}

void ASMTItem::parseASMT(std::vector<std::string> &)
{
    throw SimulationStoppingError("To be implemented.");
}

std::string ASMTItem::popOffTop(std::vector<std::string> &args)
{
    auto str = args.at(0); // Must copy string
    args.erase(args.begin());
    return str;
}

std::string ASMTItem::readStringTrimmedOffTop(std::vector<std::string> &args)
{
    // Return top string without leading and trailing whitespaces.
    std::string str = popOffTop(args);
    auto begin = std::find_if_not(str.begin(), str.end(),
                                  [](unsigned char c)
                                  { return std::isspace(c); });

    auto end = std::find_if_not(str.rbegin(), str.rend(),
                                [](unsigned char c)
                                { return std::isspace(c); })
                   .base();

    if (begin >= end)
        return "";

    return std::string(begin, end);
}

std::string ASMTItem::readStringNoSpacesOffTop(std::vector<std::string> &args)
{
    // Return top string without whitespaces.
    std::string str = popOffTop(args);
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

void ASMTItem::readStringNoSpacesOffTopEqualOrThrow(std::vector<std::string> &lines, std::string str)
{
    auto topString = readStringNoSpacesOffTop(lines);
    if (topString != str)
    {
        auto errstr = topString + " != " + str;
        throw SimulationStoppingError(errstr);
    };
}

FRowDsptr ASMTItem::readRowOfDoubles(const std::string &line)
{
    std::istringstream iss(line);
    auto readRowOfDoubles = FullRow<double>::With();
    double d;
    while (iss >> d)
    {
        readRowOfDoubles->push_back(d);
    }
    return readRowOfDoubles;
}

FRowDsptr ASMTItem::readRowOfDoublesOffTop(std::vector<std::string> &lines)
{
    auto str = popOffTop(lines);
    return readRowOfDoubles(str);
}

FRowDsptr ASMTItem::readSeriesOf(std::vector<std::string> &lines, std::string str)
{
    std::string line = lines.at(0);
    FRowDsptr row;
    readDoublesInto(line, str, row);
    lines.erase(lines.begin());
    return row;
}

FColDsptr ASMTItem::readColumnOfDoubles(const std::string &line)
{
    std::istringstream iss(line);
    auto readColumnOfDoubles = FullColumn<double>::With();
    double d;
    while (iss >> d)
    {
        readColumnOfDoubles->push_back(d);
    }
    return readColumnOfDoubles;
}

FColDsptr ASMTItem::readColumnOfDoublesOffTop(std::vector<std::string> &lines)
{
    auto str = popOffTop(lines);
    return readColumnOfDoubles(str);
}

double ASMTItem::readDouble(const std::string &line)
{
    std::istringstream iss(line);
    double d;
    iss >> d;
    return d;
}

int ASMTItem::readInt(const std::string &line)
{
    std::istringstream iss(line);
    int i;
    iss >> i;
    return i;
}

size_t ASMTItem::readSize_t(const std::string &line)
{
    std::istringstream iss(line);
    size_t i;
    iss >> i;
    return i;
}

bool ASMTItem::readBool(const std::string &line)
{
    if (line.find("true") != std::string::npos)
    {
        return true;
    }
    else if (line.find("false") != std::string::npos)
    {
        return false;
    }
    else
    {
        throw SimulationStoppingError("To be implemented.");
    }
}

std::string ASMTItem::readString(const std::string &line)
{
    // Read string without whitespaces.
    std::string str = line;
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

void ASMTItem::readName(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "Name");
    name = readStringNoSpacesOffTop(lines);
}

std::string ASMTItem::fullName(const std::string &partialName)
{
    std::string longerName = "/" + name + partialName;
    if (owner == nullptr)
    {
        return longerName;
    }
    else
    {
        return owner->fullName(longerName);
    }
}

void ASMTItem::readDoublesInto(std::string &str, std::string label, FRowDsptr &row)
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
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::updateFromMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<StateData> ASMTItem::dataFromMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::compareResults2(AnalysisType type)
{
}

void ASMTItem::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

std::string ASMTItem::reportComparisonWith(std::shared_ptr<ASMTItem> other)
{
    if (!other)
    {
        return "Missing comparison item.\n";
    }
    auto thisClassname = this->classname();
    auto otherClassname = other->classname();
    if (thisClassname != otherClassname)
    {
        return thisClassname + " != " + otherClassname + "\n";
    }
    auto thisName = this->fullName("");
    auto otherName = other->fullName("");
    if (thisName != otherName)
    {
        return thisName + " != " + otherName + "\n";
    }
    return std::string{};
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

void ASMTItem::storeOnLevel(std::ofstream &, size_t)
{
    noop();
}

void ASMTItem::storeOnLevelTabs(std::ofstream &os, size_t level)
{
    for (size_t i = 0; i < level; i++)
    {
        os << '\t';
    }
}

void ASMTItem::storeOnLevelString(std::ofstream &os, size_t level, const std::string &str)
{
    storeOnLevelTabs(os, level);
    os << str << std::endl;
}

void ASMTItem::storeOnLevelDouble(std::ofstream &os, size_t level, double value)
{
    storeOnLevelTabs(os, level);
    os << value << std::endl;
}

void ASMTItem::storeOnLevelInt(std::ofstream &os, size_t level, int i)
{
    storeOnLevelTabs(os, level);
    os << i << std::endl;
}

void ASMTItem::storeOnLevelSize_t(std::ofstream &os, size_t level, size_t i)
{
    storeOnLevelTabs(os, level);
    os << i << std::endl;
}

void ASMTItem::storeOnLevelBool(std::ofstream &os, size_t level, bool value)
{
    storeOnLevelTabs(os, level);
    if (value)
    {
        os << "true" << std::endl;
    }
    else
    {
        os << "false" << std::endl;
    }
}

void ASMTItem::storeOnLevelName(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Name");
    storeOnLevelString(os, level + 1, name);
}

void ASMTItem::storeOnTimeSeries(std::ofstream &)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTItem::storeOnArray(std::ofstream &os, const std::string &str, std::shared_ptr<std::vector<double>> arr)
{
    os << str << "\t";
    for (size_t i = 0; i < arr->size() - 1; i++)
    {
        os << arr->at(i) << '\t';
    }
    os << arr->back();
    os << std::endl;
}

void ASMTItem::storeOnArrayArray(std::ofstream &os, const std::string &str, std::shared_ptr<std::vector<FColDsptr>> arrarr, size_t ii)
{
    os << str << "\t";
    for (size_t i = 0; i < arrarr->size() - 1; i++)
    {
        os << arrarr->at(i)->at(ii) << '\t';
    }
    os << arrarr->back()->at(ii);
    os << std::endl;
}

void ASMTItem::logString(const std::string &str)
{
    std::cout << str << std::endl;
}

bool MbD::ASMTItem::hasOutputEqualTol(std::string name, double val, double inval, size_t nSig, double tol)
{
    auto tol2 = tol / 2.0;
    if (std::abs(val) < tol2 && std::abs(inval) < tol2)
        return false;
    auto ratio = val / inval;
    if (std::abs(ratio) < 1.0)
        ratio = inval / val;
    auto relDiff = std::abs(ratio) - 1.0;
    if (relDiff >= std::pow(10, -int(nSig)))
    {
        if (ratio < 0.0)
            relDiff = -relDiff;
        std::cout << "                    ";
        std::cout
            << std::left << std::setw(8) << name << " "
            << std::scientific << std::setprecision(6)
            << std::right << std::setw(14) << val
            << " != "
            << std::right << std::setw(14) << inval
            << "    relDiff = "
            << std::right << std::setw(14) << relDiff
            << ' ';
        if (std::abs(relDiff) > 1.0){
            std::cout << "! ";
        } else {
            std::cout << "  ";
        }
        return true;
    }
    return false;
}
