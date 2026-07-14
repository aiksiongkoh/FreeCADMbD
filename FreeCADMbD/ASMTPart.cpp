/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>

#include <algorithm>
#include <sstream>
#include "ASMTPart.h"
#include "ASMTMarkerTemp.h"
#include "Part.h"
#include "Units.h"
#include "System.h"
#include "EulerAngles.h"
#include "PosVelAccData.h"

using namespace MbD;

std::shared_ptr<ASMTPart> ASMTPart::With()
{
    auto inst = std::make_shared<ASMTPart>();
    inst->initialize();
    return inst;
}

std::string ASMTPart::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTSpatialContainer::reportComparisonWith(otherItem);
    if (!report.empty())
    {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTPart>(otherItem);
    if (!other)
    {
        return "Missing comparison part.";
    }
    if (!principalMassMarker && other->principalMassMarker)
    {
        return "Missing principal mass marker: " + other->principalMassMarker->fullName("") + "\n";
    }
    if (principalMassMarker && !other->principalMassMarker)
    {
        return "Missing comparison principal mass marker: " + principalMassMarker->fullName("") + "\n";
    }
    if (principalMassMarker)
    {
        report = principalMassMarker->reportComparisonWith(other->principalMassMarker);
        if (!report.empty())
        {
            return report;
        }
    }
    return std::string{};
}

void ASMTPart::parseASMT(std::vector<std::string> &lines)
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

void ASMTPart::readFeatureOrder(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "FeatureOrder");
    // featureOrder = std::make_shared<std::vector<std::shared_ptr<ASMTRefPoint>>>();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("PrincipalMassMarker") != std::string::npos; });
    // std::vector<std::string> featureOrderLines(lines.begin(), it);
    // while (!featureOrderLines.empty()) {
    //     if (featureOrderLines[0] == (leadingTabs + "\tExtrusion")) {
    //         featureOrderLines.erase(featureOrderLines.begin());
    //         auto extrusion = ASMTExtrusion::With();
    //         extrusion->owner = this;
    //         extrusion->parseASMT(featureOrderLines);
    //         featureOrder->push_back(extrusion);
    //     }
    //     else {
    //         throw SimulationStoppingError("To be implemented.");
    //     }
    // }
    lines.erase(lines.begin(), it);
}

void ASMTPart::readPrincipalMassMarker(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "PrincipalMassMarker");
    principalMassMarker = ASMTMarkerTemp::With();
    principalMassMarker->owner = this;
    principalMassMarker->parseASMT(lines);
}

void ASMTPart::readPartSeries(std::vector<std::string> &lines)
{
    std::string str = lines[0]; // Make a local copy
    std::string substr = "PartSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());

    auto inxs2 = readSeriesOf(lines, "X");
    auto inys2 = readSeriesOf(lines, "Y");
    auto inzs2 = readSeriesOf(lines, "Z");
    auto inbryxs2 = readSeriesOf(lines, "Bryantx");
    auto inbryys2 = readSeriesOf(lines, "Bryanty");
    auto inbryzs2 = readSeriesOf(lines, "Bryantz");
    auto invxs2 = readSeriesOf(lines, "VX");
    auto invys2 = readSeriesOf(lines, "VY");
    auto invzs2 = readSeriesOf(lines, "VZ");
    auto inomexs2 = readSeriesOf(lines, "OmegaX");
    auto inomeys2 = readSeriesOf(lines, "OmegaY");
    auto inomezs2 = readSeriesOf(lines, "OmegaZ");
    auto inaxs2 = readSeriesOf(lines, "AX");
    auto inays2 = readSeriesOf(lines, "AY");
    auto inazs2 = readSeriesOf(lines, "AZ");
    auto inalpxs2 = readSeriesOf(lines, "AlphaX");
    auto inalpys2 = readSeriesOf(lines, "AlphaY");
    auto inalpzs2 = readSeriesOf(lines, "AlphaZ");

    for (size_t i = 0; i < inxs2->size(); ++i)
    {
        auto data = PosVelAccData::With();
        auto lambda = [&](FRowDsptr rowx, FRowDsptr rowy, FRowDsptr rowz) -> FColDsptr
        {
            auto col = FullColumn<double>::With(3);
            col->at(0) = rowx->at(i);
            col->at(1) = rowy->at(i);
            col->at(2) = rowz->at(i);
            return col;
        };
        data->rFfF = lambda(inxs2, inys2, inzs2);
        data->bryAngFf = EulerAngles<double>::With(lambda(inbryxs2, inbryys2, inbryzs2));
        data->vFfF = lambda(invxs2, invys2, invzs2);
        data->omeFfF = lambda(inomexs2, inomeys2, inomezs2);
        data->aFfF = lambda(inaxs2, inays2, inazs2);
        data->alpFfF = lambda(inalpxs2, inalpys2, inalpzs2);
        dataSeriesIn->push_back(data);
    }

    // readXs(lines);
    // readYs(lines);
    // readZs(lines);
    // readBryantxs(lines);
    // readBryantys(lines);
    // readBryantzs(lines);
    // readVXs(lines);
    // readVYs(lines);
    // readVZs(lines);
    // readOmegaXs(lines);
    // readOmegaYs(lines);
    // readOmegaZs(lines);
    // readAXs(lines);
    // readAYs(lines);
    // readAZs(lines);
    // readAlphaXs(lines);
    // readAlphaYs(lines);
    // readAlphaZs(lines);
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

ASMTPart *ASMTPart::part()
{
    return this;
}

void ASMTPart::createMbD()
{
    // Create MbD in SI units
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
}

void ASMTPart::updateFromMbD()
{
    auto data = dataFromMbD();
    dataSeries->push_back(data);

    auto mbdUnts = mbdUnits();
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    auto rOcmO = mbdPart->qX()->times(mbdUnts->length);
    auto aAOp = mbdPart->aAOp();
    // std::cout << "aAOp" << *aAOp << std::endl;
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
    // std::cout << "bry " << *bryantAngles << std::endl;
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

std::shared_ptr<StateData> ASMTPart::dataFromMbD()
{
    auto mbdUnts = mbdUnits();
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    auto rOcmO = mbdPart->qX()->times(mbdUnts->length);
    auto aAOp = mbdPart->aAOp();
    // std::cout << "aAOp" << *aAOp << std::endl;
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

    auto data = PosVelAccData::With();
    data->rFfF = rOPO;
    data->aAFf = aAOP;
    data->bryAngFf = aAOP->bryantAngles();
    data->vFfF = vOPO;
    data->omeFfF = omeOPO;
    data->aFfF = aOPO;
    data->alpFfF = alpOPO;
    return data;
}

void ASMTSpatialContainer::updateMbDFromPosition3D(FColDsptr vec)
{
    position3D = vec;
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    mbdPart->qX(rOcmO()->times(asmtUnits()->length));
}

void ASMTPart::storeOnLevel(std::ofstream &os, size_t level)
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

void ASMTPart::storeOnLevelMassMarker(std::ofstream &os, size_t level) const
{
    principalMassMarker->storeOnLevel(os, level);
}

void ASMTPart::storeOnTimeSeries(std::ofstream &os)
{
    os << "PartSeries\t" << fullName("") << std::endl;
    ASMTSpatialContainer::storeOnTimeSeries(os);
}
