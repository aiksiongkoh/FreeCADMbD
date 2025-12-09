/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTItemIJ.h"
#include "ASMTAssembly.h"
#include "EndFrameqc.h"
#include "ForceTorqueData.h"

using namespace MbD;

std::shared_ptr<ASMTItemIJ> ASMTItemIJ::With()
{
    auto inst = std::make_shared<ASMTItemIJ>();
    inst->initialize();
    return inst;
}

void ASMTItemIJ::initialize()
{
    //ASMTItem::initialize();
    cFIO = std::make_shared<std::vector<std::shared_ptr<FullColumn<double>>>>();
    cTIO = std::make_shared<std::vector<std::shared_ptr<FullColumn<double>>>>();
}

void ASMTItemIJ::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    readMarkerI(lines);
    readMarkerJ(lines);
}

void ASMTItemIJ::setMarkerI(std::shared_ptr<ASMTMarker> mkrI)
{
    markerI = mkrI;
}

void ASMTItemIJ::setMarkerJ(std::shared_ptr<ASMTMarker> mkrJ)
{
    markerJ = mkrJ;
}

void ASMTItemIJ::readMarkerI(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MarkerI");
    auto markerName = readStringNoSpacesOffTop(lines);
    markerI = root()->markerAt(markerName);
}

void ASMTItemIJ::readMarkerJ(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "MarkerJ");
    auto markerName = readStringNoSpacesOffTop(lines);
    markerJ = root()->markerAt(markerName);
}

void ASMTItemIJ::readFXonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "FXonI", infxs);
    lines.erase(lines.begin());
}

void ASMTItemIJ::readFYonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "FYonI", infys);
    lines.erase(lines.begin());
}

void ASMTItemIJ::readFZonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "FZonI", infzs);
    lines.erase(lines.begin());
}

void ASMTItemIJ::readTXonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "TXonI", intxs);
    lines.erase(lines.begin());
}

void ASMTItemIJ::readTYonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "TYonI", intys);
    lines.erase(lines.begin());
}

void ASMTItemIJ::readTZonIs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "TZonI", intzs);
    lines.erase(lines.begin());
}

void ASMTItemIJ::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTItem::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "MarkerI");
    storeOnLevelString(os, level + 2, markerI->fullName(""));
    storeOnLevelString(os, level + 1, "MarkerJ");
    storeOnLevelString(os, level + 2, markerJ->fullName(""));
}

void ASMTItemIJ::storeOnTimeSeries(std::ofstream& os)
{
    auto n = cFIO->size();
    os << "FXonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cFIO->at(i)->at(0) << '\t';
    }
    os << std::endl;
    os << "FYonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cFIO->at(i)->at(1) << '\t';
    }
    os << std::endl;
    os << "FZonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cFIO->at(i)->at(2) << '\t';
    }
    os << std::endl;
    os << "TXonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cTIO->at(i)->at(0) << '\t';
    }
    os << std::endl;
    os << "TYonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cTIO->at(i)->at(1) << '\t';
    }
    os << std::endl;
    os << "TZonI\t";
    for (size_t i = 0; i < n; i++)
    {
        os << cTIO->at(i)->at(2) << '\t';
    }
    os << std::endl;
}

FMatDsptr ASMTItemIJ::aAOI(size_t i)
{
    return markerI->aAOf(i);
}

FColDsptr ASMTItemIJ::aFII(size_t i)
{
    auto aAIO = aAOI(i)->transpose();
    return aAIO->timesFullColumn(aFIO(i));
}

FColDsptr ASMTItemIJ::aFIO(size_t i)
{
    if (cFIO == nullptr || cFIO->empty()) {
        auto forTor = std::static_pointer_cast<ForceTorqueData>(dataSeries->at(i));
        return forTor->aFIO;
    }
    else {
        return cFIO->at(i);
    }
}

FColDsptr ASMTItemIJ::aTII(size_t i)
{
    auto aAIO = aAOI(i)->transpose();
    return aAIO->timesFullColumn(aTIO(i));
}

FColDsptr ASMTItemIJ::aTIO(size_t i)
{
    if (cTIO == nullptr || cTIO->empty()) {
        auto forTor = std::static_pointer_cast<ForceTorqueData>(dataSeries->at(i));
        return forTor->aTIO;
    }
    else {
        return cTIO->at(i);
    }
}

bool ASMTItemIJ::isJoint()
{
    return false;
}

bool ASMTItemIJ::isMotion()
{
    return false;
}

bool ASMTItemIJ::isForceTorque()
{
    return false;
}
