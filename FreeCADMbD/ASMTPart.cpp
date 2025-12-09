/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTPart.h"
#include "ASMTPrincipalMassMarker.h"
#include "Part.h"
#include <algorithm>

using namespace MbD;

std::shared_ptr<ASMTPart> ASMTPart::With()
{
    auto inst = std::make_shared<ASMTPart>();
    inst->initialize();
    return inst;
}

void ASMTPart::parseASMT(std::vector<std::string>& lines)
{
    readName(lines);
    readPosition3D(lines);
    readRotationMatrix(lines);
    readVelocity3D(lines);
    readOmega3D(lines);
    readFeatureOrder(lines);
    readPrincipalMassMarker(lines);
    readRefPoints(lines);
    readRefCurves(lines);
    readRefSurfaces(lines);
}

void ASMTPart::readFeatureOrder(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "FeatureOrder");
    //featureOrder = std::make_shared<std::vector<std::shared_ptr<ASMTRefPoint>>>();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
        return s.find("PrincipalMassMarker") != std::string::npos;
        });
    //std::vector<std::string> featureOrderLines(lines.begin(), it);
    //while (!featureOrderLines.empty()) {
    //    if (featureOrderLines[0] == (leadingTabs + "\tExtrusion")) {
    //        featureOrderLines.erase(featureOrderLines.begin());
    //        auto extrusion = ASMTExtrusion::With();
    //        extrusion->owner = this;
    //        extrusion->parseASMT(featureOrderLines);
    //        featureOrder->push_back(extrusion);
    //    }
    //    else {
    //        throw SimulationStoppingError("To be implemented.");
    //    }
    //}
    lines.erase(lines.begin(), it);
}

void ASMTPart::readPrincipalMassMarker(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "PrincipalMassMarker");
    principalMassMarker = ASMTPrincipalMassMarker::With();
    principalMassMarker->owner = this;
    principalMassMarker->parseASMT(lines);
}

void ASMTPart::readPartSeries(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    std::string substr = "PartSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());
    //xs, ys, zs, bryxs, bryys, bryzs
    readXs(lines);
    readYs(lines);
    readZs(lines);
    readBryantxs(lines);
    readBryantys(lines);
    readBryantzs(lines);
    readVXs(lines);
    readVYs(lines);
    readVZs(lines);
    readOmegaXs(lines);
    readOmegaYs(lines);
    readOmegaZs(lines);
    readAXs(lines);
    readAYs(lines);
    readAZs(lines);
    readAlphaXs(lines);
    readAlphaYs(lines);
    readAlphaZs(lines);
}

FColDsptr ASMTPart::vOcmO()
{
    auto& rOPO = position3D;
    auto& vOPO = velocity3D;
    auto& omeOPO = omega3D;
    auto rPcmO = rOcmO()->minusFullColumn(rOPO);
    return vOPO->plusFullColumn(omeOPO->cross(rPcmO));
}

FColDsptr ASMTPart::omeOpO()
{
    return omega3D;
}

ASMTPart* ASMTPart::part()
{
    return this;
}

void ASMTPart::createMbD()
{
    ASMTSpatialContainer::createMbD();
    if (isFixed) std::static_pointer_cast<Part>(mbdObject)->asFixed();
}

void ASMTPart::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "Part");
    storeOnLevelName(os, level + 1);
    storeOnLevelPosition(os, level + 1);
    storeOnLevelRotationMatrix(os, level + 1);
    storeOnLevelVelocity(os, level + 1);
    storeOnLevelOmega(os, level + 1);
    storeOnLevelString(os, level + 1, "FeatureOrder");
    storeOnLevelMassMarker(os, level + 1);
    storeOnLevelRefPoints(os, level + 1);
    storeOnLevelRefCurves(os, level + 1);
    storeOnLevelRefSurfaces(os, level + 1);
}

void ASMTPart::storeOnLevelMassMarker(std::ofstream& os, size_t level) const
{
    principalMassMarker->storeOnLevel(os, level);
}

void ASMTPart::storeOnTimeSeries(std::ofstream& os)
{
    os << "PartSeries\t" << fullName("") << std::endl;
    ASMTSpatialContainer::storeOnTimeSeries(os);
}
