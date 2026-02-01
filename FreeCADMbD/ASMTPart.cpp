/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include <algorithm>
#include "ASMTPart.h"
#include "ASMTMarkerTemp.h"
#include "Part.h"
#include "Units.h"
#include "System.h"

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
    principalMassMarker = ASMTMarkerTemp::With();
    principalMassMarker->owner = this;
    principalMassMarker->parseASMT(lines);
}

void ASMTPart::readPartSeries(std::vector<std::string>& lines)
{
    std::string str = lines[0]; // Make a local copy
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

void ASMTPart::setPrincipalMassMarker(std::shared_ptr<ASMTMarkerTemp> aJ)
{
    principalMassMarker = aJ;
    aJ->owner = this;
}

FColDsptr ASMTPart::rOcmO()
{
    auto rOPO = position3D;
    auto aAOP = rotationMatrix;
    auto rPcmP = principalMassMarker->position3D;
    auto rOcmO = rOPO->plusFullColumn(aAOP->timesFullColumn(rPcmP));
    return rOcmO;
}

std::shared_ptr<EulerParameters<double>> ASMTPart::qEp()
{
    auto aAOP = rotationMatrix;
    auto aAPcm = principalMassMarker->rotationMatrix;
    auto aAOcm = aAOP->timesFullMatrix(aAPcm);
    return aAOcm->asEulerParameters();
}

FColDsptr ASMTPart::vOcmO()
{
    auto rOPO = position3D;
    auto vOPO = velocity3D;
    auto omeOPO = omega3D;
    auto rPcmO = rOcmO()->minusFullColumn(rOPO);
    return vOPO->plusFullColumn(omeOPO->cross(rPcmO));
}

FColDsptr ASMTPart::omeOpO()
{
    return omega3D;
}

void ASMTPart::initialize()
{
    ASMTSpatialContainer::initialize();
    setPrincipalMassMarker(ASMTMarkerTemp::With());
}

ASMTPart* ASMTPart::part()
{
    return this;
}

void ASMTPart::createMbD()
{
    //Create MbD in SI units
    auto asmtUnts = asmtUnits();
    auto mbdPart = Part::With();
    mbdObject = mbdPart;
    mbdPart->name = fullName("");
    principalMassMarker->createMbD();
    mbdPart->m = principalMassMarker->mass * asmtUnts->mass;
    mbdPart->aJ = principalMassMarker->momentOfInertias->times(asmtUnts->aJ);
    mbdPart->qX(rOcmO()->times(asmtUnts->length));
    mbdPart->qE(qEp());
    mbdPart->qXdot(vOcmO()->times(asmtUnts->velocity));
    mbdPart->omeOpO(omeOpO()->times(asmtUnts->omega));
    mbdPart->qXddot(std::make_shared<FullColumn<double>>(3, 0));
    mbdPart->qEddot(std::make_shared<FullColumn<double>>(4, 0));
    mbdSys()->addPart(mbdPart);
    ASMTSpatialContainer::createMbD();
    if (isFixed) std::static_pointer_cast<Part>(mbdObject)->asFixed();
}

void ASMTPart::updateFromMbD()
{
    auto mbdUnts = mbdUnits();
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    auto rOcmO = mbdPart->qX()->times(mbdUnts->length);
    auto aAOp = mbdPart->aAOp();
    //std::cout << "aAOp" << *aAOp << std::endl;
    auto vOcmO = mbdPart->qXdot()->times(mbdUnts->velocity);
    auto omeOPO = mbdPart->omeOpO()->times(mbdUnts->omega);
    omega3D = omeOPO;
    auto aOcmO = mbdPart->qXddot()->times(mbdUnts->acceleration);
    auto alpOPO = mbdPart->alpOpO()->times(mbdUnts->alpha);
    alpha3D = alpOPO;
    auto rPcmP = principalMassMarker->position3D;
    auto aAPp = principalMassMarker->rotationMatrix;
    auto aAOP = aAOp->timesTransposeFullMatrix(aAPp);
    rotationMatrix = aAOP;
    auto rPcmO = aAOP->timesFullColumn(rPcmP);
    auto rOPO = rOcmO->minusFullColumn(rPcmO);
    position3D = rOPO;
    auto vOPO = vOcmO->minusFullColumn(omeOPO->cross(rPcmO));
    velocity3D = vOPO;
    auto aOPO = aOcmO->minusFullColumn(alpOPO->cross(rPcmO))->minusFullColumn(omeOPO->cross(omeOPO->cross(rPcmO)));
    acceleration3D = aOPO;
    xs->push_back(rOPO->at(0));
    ys->push_back(rOPO->at(1));
    zs->push_back(rOPO->at(2));
    auto bryantAngles = aAOP->bryantAngles();
    bryxs->push_back(bryantAngles->at(0));
    bryys->push_back(bryantAngles->at(1));
    bryzs->push_back(bryantAngles->at(2));
    //std::cout << "bry " << *bryantAngles << std::endl;
    vxs->push_back(vOPO->at(0));
    vys->push_back(vOPO->at(1));
    vzs->push_back(vOPO->at(2));
    omexs->push_back(omeOPO->at(0));
    omeys->push_back(omeOPO->at(1));
    omezs->push_back(omeOPO->at(2));
    axs->push_back(aOPO->at(0));
    ays->push_back(aOPO->at(1));
    azs->push_back(aOPO->at(2));
    alpxs->push_back(alpOPO->at(0));
    alpys->push_back(alpOPO->at(1));
    alpzs->push_back(alpOPO->at(2));
}

void ASMTSpatialContainer::updateMbDFromPosition3D(FColDsptr vec)
{
    position3D = vec;
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    mbdPart->qX(rOcmO()->times(asmtUnits()->length));
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
