/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <algorithm>
#include <fstream>    

#include "ASMTSpatialContainer.h"
#include "Units.h"
#include "Part.h"
#include "System.h"
#include "ASMTRefPoint.h"
#include "ASMTRefCurve.h"
#include "ASMTRefSurface.h"
#include "PosVelAccData.h"
#include "SimulationStoppingError.h"


using namespace MbD;

std::shared_ptr<ASMTSpatialContainer> ASMTSpatialContainer::With()
{
    auto inst = std::make_shared<ASMTSpatialContainer>();
    inst->initialize();
    return inst;
}

void ASMTSpatialContainer::initialize()
{
    refPoints = std::make_shared<std::vector<std::shared_ptr<ASMTRefPoint>>>();
    refCurves = std::make_shared<std::vector<std::shared_ptr<ASMTRefCurve>>>();
    refSurfaces = std::make_shared<std::vector<std::shared_ptr<ASMTRefSurface>>>();

    xs = FullRow<double>::With();
    ys = FullRow<double>::With();
    zs = FullRow<double>::With();
    bryxs = FullRow<double>::With();
    bryys = FullRow<double>::With();
    bryzs = FullRow<double>::With();
    vxs = FullRow<double>::With();
    vys = FullRow<double>::With();
    vzs = FullRow<double>::With();
    omexs = FullRow<double>::With();
    omeys = FullRow<double>::With();
    omezs = FullRow<double>::With();
    axs = FullRow<double>::With();
    ays = FullRow<double>::With();
    azs = FullRow<double>::With();
    alpxs = FullRow<double>::With();
    alpys = FullRow<double>::With();
    alpzs = FullRow<double>::With();
}

void ASMTSpatialContainer::setPrincipalMassMarker(std::shared_ptr<ASMTPrincipalMassMarker> aJ)
{
    principalMassMarker = aJ;
}

void ASMTSpatialContainer::readRefPoints(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RefPoints");
    refPoints->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
        return s.find("RefCurves") != std::string::npos;
        });
    std::vector<std::string> refPointsLines(lines.begin(), it);
    while (!refPointsLines.empty()) {
        readRefPoint(refPointsLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefPoint(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RefPoint");
    auto refPoint = ASMTRefPoint::With();
    refPoint->owner = this;
    refPoint->parseASMT(lines);
    refPoints->push_back(refPoint);
}

void ASMTSpatialContainer::readRefCurves(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RefCurves");
    refCurves->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
        return s.find("RefSurfaces") != std::string::npos;
        });
    std::vector<std::string> refCurvesLines(lines.begin(), it);
    while (!refCurvesLines.empty()) {
        readRefCurve(refCurvesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefCurve(std::vector<std::string>&)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSpatialContainer::readRefSurfaces(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RefSurfaces");
    refSurfaces->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
        return s.find("Part") != std::string::npos;
        });
    std::vector<std::string> refSurfacesLines(lines.begin(), it);
    while (!refSurfacesLines.empty()) {
        readRefSurface(refSurfacesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefSurface(std::vector<std::string>&)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSpatialContainer::readXs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "X", inxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readYs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Y", inys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readZs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Z", inzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantxs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryantx", inbryxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantys(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryanty", inbryys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantzs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryantz", inbryzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVXs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VX", invxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVYs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VY", invys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVZs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VZ", invzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaXs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaX", inomexs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaYs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaY", inomeys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaZs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaZ", inomezs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAXs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AX", inaxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAYs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AY", inays);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAZs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AZ", inazs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaXs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaX", inalpxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaYs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaY", inalpys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaZs(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaZ", inalpzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::createMbD()
{
    //Create MbD in SI units
    auto asmtUnts = asmtUnits();
    auto mbdPart = Part::With();
    mbdObject = mbdPart;
    mbdPart->name = fullName("");
    mbdPart->m = principalMassMarker->mass * asmtUnts->mass;
    mbdPart->aJ = principalMassMarker->momentOfInertias->times(asmtUnts->aJ);
    mbdPart->qX(rOcmO()->times(asmtUnts->length));
    mbdPart->qE(qEp());
    mbdPart->qXdot(vOcmO()->times(asmtUnts->velocity));
    mbdPart->omeOpO(omeOpO()->times(asmtUnts->omega));
    mbdPart->qXddot(std::make_shared<FullColumn<double>>(3, 0));
    mbdPart->qEddot(std::make_shared<FullColumn<double>>(4, 0));
    mbdSys()->addPart(mbdPart);
    for (auto& refPoint : *refPoints) {
        refPoint->createMbD();
    }
    for (auto& refCurve : *refCurves) {
        refCurve->createMbD();
    }
    for (auto& refSurface : *refSurfaces) {
        refSurface->createMbD();
    }
}

//void ASMTSpatialContainer::createMbD()
//{
//    auto mbdPart = Part::With();
//    mbdObject = mbdPart;
//    mbdPart->name = fullName("");
//    mbdPart->m = principalMassMarker->mass / mbdUnits()->mass;
//    mbdPart->aJ = principalMassMarker->momentOfInertias->times(1.0 / mbdUnits()->aJ);
//    mbdPart->qX(rOcmO()->times(1.0 / mbdUnits()->length));
//    mbdPart->qE(qEp());
//    mbdPart->qXdot(vOcmO()->times(1.0 / mbdUnits()->velocity));
//    mbdPart->omeOpO(omeOpO()->times(1.0 / mbdUnits()->omega));
//    mbdPart->qXddot(std::make_shared<FullColumn<double>>(3, 0));
//    mbdPart->qEddot(std::make_shared<FullColumn<double>>(4, 0));
//    mbdSys()->addPart(mbdPart);
//    for (auto& refPoint : *refPoints) {
//        refPoint->createMbD();
//    }
//    for (auto& refCurve : *refCurves) {
//        refCurve->createMbD();
//    }
//    for (auto& refSurface : *refSurfaces) {
//        refSurface->createMbD();
//    }
//}

void ASMTSpatialContainer::updateMbDFromPosition3D(FColDsptr vec)
{
    position3D = vec;
    auto mbdPart = std::static_pointer_cast<Part>(mbdObject);
    mbdPart->qX(rOcmO()->times(asmtUnits()->length));
}

FColDsptr ASMTSpatialContainer::rOcmO()
{
    auto& rOPO = position3D;
    auto& aAOP = rotationMatrix;
    auto& rPcmP = principalMassMarker->position3D;
    auto rOcmO = rOPO->plusFullColumn(aAOP->timesFullColumn(rPcmP));
    return rOcmO;
}

std::shared_ptr<EulerParameters<double>> ASMTSpatialContainer::qEp()
{
    auto& aAOP = rotationMatrix;
    auto& aAPcm = principalMassMarker->rotationMatrix;
    auto aAOcm = aAOP->timesFullMatrix(aAPcm);
    return aAOcm->asEulerParameters();
}

FColDsptr ASMTSpatialContainer::vOcmO()
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr ASMTSpatialContainer::omeOpO()
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

ASMTSpatialContainer* ASMTSpatialContainer::partOrAssembly()
{
    return this;
}

void ASMTSpatialContainer::updateFromMbD()
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
    auto& rPcmP = principalMassMarker->position3D;
    auto& aAPp = principalMassMarker->rotationMatrix;
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

void ASMTSpatialContainer::compareResults(AnalysisType)
{
    if (inxs == nullptr || inxs->empty()) return;
    auto mbdUnts = mbdUnits();
    auto factor = 1.0e-3;
    auto lengthTol = mbdUnts->length * factor;
    auto angleTol = mbdUnts->angle * factor;
    auto velocityTol = mbdUnts->velocity * factor;
    auto omegaTol = mbdUnts->omega * factor;
    auto accelerationTol = mbdUnts->acceleration * factor;
    auto alphaTol = mbdUnts->alpha * factor;
    auto i = xs->size() - 1;
    //Pos
    if (!Numeric::equaltol(xs->at(i), inxs->at(i), lengthTol)) {
        std::cout << i << " xs " << xs->at(i) << " != " << inxs->at(i) << " tol = " << lengthTol << std::endl;
    }
    if (!Numeric::equaltol(ys->at(i), inys->at(i), lengthTol)) {
        std::cout << i << " ys " << ys->at(i) << " != " << inys->at(i) << " tol = " << lengthTol << std::endl;
    }
    if (!Numeric::equaltol(zs->at(i), inzs->at(i), lengthTol)) {
        std::cout << i << " zs " << zs->at(i) << " != " << inzs->at(i) << " tol = " << lengthTol << std::endl;
    }
    if (!Numeric::equaltol(bryxs->at(i), inbryxs->at(i), angleTol)) {
        std::cout << i << " bryxs " << bryxs->at(i) << " != " << inbryxs->at(i) << " tol = " << angleTol << std::endl;
    }
    if (!Numeric::equaltol(bryys->at(i), inbryys->at(i), angleTol)) {
        std::cout << i << " bryys " << bryys->at(i) << " != " << inbryys->at(i) << " tol = " << angleTol << std::endl;
    }
    if (!Numeric::equaltol(bryzs->at(i), inbryzs->at(i), angleTol)) {
        std::cout << i << " bryzs " << bryzs->at(i) << " != " << inbryzs->at(i) << " tol = " << angleTol << std::endl;
    }
    //Vel
    if (!Numeric::equaltol(vxs->at(i), invxs->at(i), velocityTol)) {
        std::cout << i << " vxs " << vxs->at(i) << " != " << invxs->at(i) << " tol = " << velocityTol << std::endl;
    }
    if (!Numeric::equaltol(vys->at(i), invys->at(i), velocityTol)) {
        std::cout << i << " vys " << vys->at(i) << " != " << invys->at(i) << " tol = " << velocityTol << std::endl;
    }
    if (!Numeric::equaltol(vzs->at(i), invzs->at(i), velocityTol)) {
        std::cout << i << " vzs " << vzs->at(i) << " != " << invzs->at(i) << " tol = " << velocityTol << std::endl;
    }
    if (!Numeric::equaltol(omexs->at(i), inomexs->at(i), omegaTol)) {
        std::cout << i << " omexs " << omexs->at(i) << " != " << inomexs->at(i) << " tol = " << omegaTol << std::endl;
    }
    if (!Numeric::equaltol(omeys->at(i), inomeys->at(i), omegaTol)) {
        std::cout << i << " omeys " << omeys->at(i) << " != " << inomeys->at(i) << " tol = " << omegaTol << std::endl;
    }
    if (!Numeric::equaltol(omezs->at(i), inomezs->at(i), omegaTol)) {
        std::cout << i << " omezs " << omezs->at(i) << " != " << inomezs->at(i) << " tol = " << omegaTol << std::endl;
    }
    //Acc
    if (!Numeric::equaltol(axs->at(i), inaxs->at(i), accelerationTol)) {
        std::cout << i << " axs " << axs->at(i) << " != " << inaxs->at(i) << " tol = " << accelerationTol << std::endl;
    }
    if (!Numeric::equaltol(ays->at(i), inays->at(i), accelerationTol)) {
        std::cout << i << " ays " << ays->at(i) << " != " << inays->at(i) << " tol = " << accelerationTol << std::endl;
    }
    if (!Numeric::equaltol(azs->at(i), inazs->at(i), accelerationTol)) {
        std::cout << i << " azs " << azs->at(i) << " != " << inazs->at(i) << " tol = " << accelerationTol << std::endl;
    }
    if (!Numeric::equaltol(alpxs->at(i), inalpxs->at(i), alphaTol)) {
        std::cout << i << " alpxs " << alpxs->at(i) << " != " << inalpxs->at(i) << " tol = " << alphaTol << std::endl;
    }
    if (!Numeric::equaltol(alpys->at(i), inalpys->at(i), alphaTol)) {
        std::cout << i << " alpys " << alpys->at(i) << " != " << inalpys->at(i) << " tol = " << alphaTol << std::endl;
    }
    if (!Numeric::equaltol(alpzs->at(i), inalpzs->at(i), alphaTol)) {
        std::cout << i << " alpzs " << alpzs->at(i) << " != " << inalpzs->at(i) << " tol = " << alphaTol << std::endl;
    }
}

void ASMTSpatialContainer::outputResults(AnalysisType)
{
    if (inxs != nullptr && !inxs->empty()) return;
    auto i = xs->size() - 1;
    std::cout << i << " ";
    std::cout << xs->at(i) << ", " << ys->at(i) << ", " << zs->at(i) << ", ";
    std::cout << bryxs->at(i) << ", " << bryys->at(i) << ", " << bryzs->at(i) << std::endl;
}

void ASMTSpatialContainer::addRefPoint(std::shared_ptr<ASMTRefPoint> refPoint)
{
    refPoints->push_back(refPoint);
    refPoint->owner = this;
}

void ASMTSpatialContainer::addMarker(std::shared_ptr<ASMTMarker> marker)
{
    auto refPoint = ASMTRefPoint::With();
    addRefPoint(refPoint);
    refPoint->addMarker(marker);
}

std::string ASMTSpatialContainer::generateUniqueMarkerName() const
{
    auto aItemList = markerList();
    auto markerNames = std::vector<std::string>();
    for (auto& mkr : *aItemList) {
        markerNames.push_back(mkr->name);
    }
    std::stringstream ss;
    auto count = 0;
    while (true) {
        ss.str("");
        ss << "Marker";
        ss << count;
        if (std::find(markerNames.begin(), markerNames.end(), ss.str()) == markerNames.end()) break;
        count++;
    }
    return ss.str();
}

std::shared_ptr<std::vector<std::shared_ptr<ASMTMarker>>> ASMTSpatialContainer::markerList() const
{
    auto markers = std::make_shared<std::vector<std::shared_ptr<ASMTMarker>>>();
    for (auto& refPoint : *refPoints) {
        auto& refmarkers = refPoint->markers;
        markers->insert(markers->end(), refmarkers->begin(), refmarkers->end());
    }
    return markers;
}

void ASMTSpatialContainer::storeOnLevel(std::ofstream& os, size_t level)
{
    ASMTSpatialItem::storeOnLevel(os, level);
    storeOnLevelVelocity(os, level + 1);
    storeOnLevelOmega(os, level + 1);
    storeOnLevelRefPoints(os, level + 1);
    storeOnLevelRefCurves(os, level + 1);
    storeOnLevelRefSurfaces(os, level + 1);
}

void ASMTSpatialContainer::setVelocity3D(FColDsptr vec)
{
    velocity3D = vec;
}

void ASMTSpatialContainer::setOmega3D(FColDsptr vec)
{
    omega3D = vec;
}

void ASMTSpatialContainer::readVelocity3D(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Velocity3D");
    std::istringstream iss(lines[0]);
    velocity3D = FullColumn<double>::With();
    double d;
    while (iss >> d) {
        velocity3D->push_back(d);
    }
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmega3D(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Omega3D");
    std::istringstream iss(lines[0]);
    omega3D = FullColumn<double>::With();
    double d;
    while (iss >> d) {
        omega3D->push_back(d);
    }
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::setVelocity3D(double a, double b, double c)
{
    velocity3D = std::make_shared<FullColumn<double>>(ListD{ a, b, c });
}

void ASMTSpatialContainer::setOmega3D(double a, double b, double c)
{
    omega3D = std::make_shared<FullColumn<double>>(ListD{ a, b, c });
}

void ASMTSpatialContainer::storeOnLevelVelocity(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "Velocity3D");
    if (vxs == nullptr || vxs->empty()) {
        storeOnLevelArray(os, level + 1, *velocity3D);
    }
    else {
        auto array = getVelocity3D(0);
        storeOnLevelArray(os, level + 1, *array);
    }
}

void ASMTSpatialContainer::storeOnLevelOmega(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "Omega3D");
    if (omexs == nullptr || omexs->empty()) {
        storeOnLevelArray(os, level + 1, *omega3D);
    }
    else {
        auto array = getOmega3D(0);
        storeOnLevelArray(os, level + 1, *array);
    }
}

void ASMTSpatialContainer::storeOnLevelRefPoints(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RefPoints");
    for (auto& refPoint : *refPoints)
    {
        refPoint->storeOnLevel(os, level + 1);
    }
}

void ASMTSpatialContainer::storeOnLevelRefCurves(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RefCurves");
    for (auto& refCurve : *refCurves)
    {
        refCurve->storeOnLevel(os, level);
    }
}

void ASMTSpatialContainer::storeOnLevelRefSurfaces(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RefSurfaces");
    for (auto& refSurface : *refSurfaces)
    {
        refSurface->storeOnLevel(os, level);
    }
}

void ASMTSpatialContainer::storeOnTimeSeries(std::ofstream& os)
{
    os << "X\t";
    for (size_t i = 0; i < xs->size(); i++)
    {
        os << xs->at(i) << '\t';
    }
    os << std::endl;
    os << "Y\t";
    for (size_t i = 0; i < ys->size(); i++)
    {
        os << ys->at(i) << '\t';
    }
    os << std::endl;
    os << "Z\t";
    for (size_t i = 0; i < zs->size(); i++)
    {
        os << zs->at(i) << '\t';
    }
    os << std::endl;
    os << "Bryantx\t";
    for (size_t i = 0; i < bryxs->size(); i++)
    {
        os << bryxs->at(i) << '\t';
    }
    os << std::endl;
    os << "Bryanty\t";
    for (size_t i = 0; i < bryys->size(); i++)
    {
        os << bryys->at(i) << '\t';
    }
    os << std::endl;
    os << "Bryantz\t";
    for (size_t i = 0; i < bryzs->size(); i++)
    {
        os << bryzs->at(i) << '\t';
    }
    os << std::endl;
    os << "VX\t";
    for (size_t i = 0; i < vxs->size(); i++)
    {
        os << vxs->at(i) << '\t';
    }
    os << std::endl;
    os << "VY\t";
    for (size_t i = 0; i < vys->size(); i++)
    {
        os << vys->at(i) << '\t';
    }
    os << std::endl;
    os << "VZ\t";
    for (size_t i = 0; i < vzs->size(); i++)
    {
        os << vzs->at(i) << '\t';
    }
    os << std::endl;
    os << "OmegaX\t";
    for (size_t i = 0; i < omexs->size(); i++)
    {
        os << omexs->at(i) << '\t';
    }
    os << std::endl;
    os << "OmegaY\t";
    for (size_t i = 0; i < omeys->size(); i++)
    {
        os << omeys->at(i) << '\t';
    }
    os << std::endl;
    os << "OmegaZ\t";
    for (size_t i = 0; i < omezs->size(); i++)
    {
        os << omezs->at(i) << '\t';
    }
    os << std::endl;
    os << "AX\t";
    for (size_t i = 0; i < axs->size(); i++)
    {
        os << axs->at(i) << '\t';
    }
    os << std::endl;
    os << "AY\t";
    for (size_t i = 0; i < ays->size(); i++)
    {
        os << ays->at(i) << '\t';
    }
    os << std::endl;
    os << "AZ\t";
    for (size_t i = 0; i < azs->size(); i++)
    {
        os << azs->at(i) << '\t';
    }
    os << std::endl;
    os << "AlphaX\t";
    for (size_t i = 0; i < alpxs->size(); i++)
    {
        os << alpxs->at(i) << '\t';
    }
    os << std::endl;
    os << "AlphaY\t";
    for (size_t i = 0; i < alpys->size(); i++)
    {
        os << alpys->at(i) << '\t';
    }
    os << std::endl;
    os << "AlphaZ\t";
    for (size_t i = 0; i < alpzs->size(); i++)
    {
        os << alpzs->at(i) << '\t';
    }
    os << std::endl;
}

FColDsptr ASMTSpatialContainer::getVelocity3D(size_t i) const
{
    auto vec3 = std::make_shared<FullColumn<double>>(3);
    vec3->atiput(0, vxs->at(i));
    vec3->atiput(1, vys->at(i));
    vec3->atiput(2, vzs->at(i));
    return vec3;
}

FColDsptr ASMTSpatialContainer::getOmega3D(size_t i) const
{
    auto vec3 = std::make_shared<FullColumn<double>>(3);
    vec3->atiput(0, omexs->at(i));
    vec3->atiput(1, omeys->at(i));
    vec3->atiput(2, omezs->at(i));
    return vec3;
}

void ASMTSpatialContainer::updateFromInputState()
{
    setPosition3D(getPosition3D(0));
    setRotationMatrix(getRotationMatrix(0));
    setVelocity3D(getVelocity3D(0));
    setOmega3D(getOmega3D(0));
    for (auto& refPoint : *refPoints) {
        refPoint->updateFromInputState();
    }

}

std::shared_ptr<StateData> ASMTSpatialContainer::dataFromMbD()
{
    //"
    //P := part frame. 
    //p := principal frame at cm. 
    //rOcmO := rOPO + aAOP*rPcmP. 
    //aAOp := aAOP*aAPp. 
    //vOcmO := vOPO + aAdotOP*rPcmP 
    //:= vOPO + (omeOPO cross: aAOP*rPcmP). 
    //omeOpO := omeOPO. 
    //aOcmO := aOPO + aAddotOP*rPcmP 
    //:= aOPO + (alpOPO cross: aAOP*rPcmP) + (omeOPO cross: (omeOPO cross: aAOP*rPcmP)). 
    //alpOpO := alpOPO. 
    //
    //Therefore 
    //aAOP := aAOp*aAPpT 
    //rOPO := rOcmO - aAOP*rPcmP. 
    //omeOPO := omeOpO. 
    //vOPO    := vOcmO - (omeOPO cross: aAOP*rPcmP). 
    //alpOPO := alpOpO. 
    //aOPO    := aOcmO - (alpOPO cross: aAOP*rPcmP) - (omeOPO cross: (omeOPO cross: 
    //aAOP*rPcmP)). 
    //"

    auto answer = PosVelAccData::With();
    answer->rFfF = rOPO();
    answer->aAFf = aAOP();
    answer->vFfF = vOPO();
    answer->omeFfF = omeOPO();
    answer->aFfF = aOPO();
    answer->alpFfF = alpOPO();
    return answer;
}

FColDsptr ASMTSpatialContainer::rOPO()
{
    return position3D;
}

FMatDsptr ASMTSpatialContainer::aAOP()
{
    return rotationMatrix;
}

FColDsptr ASMTSpatialContainer::vOPO()
{
    return velocity3D;
}

FColDsptr ASMTSpatialContainer::omeOPO()
{
    return omega3D;
}

FColDsptr ASMTSpatialContainer::aOPO()
{
    return acceleration3D;
}

FColDsptr ASMTSpatialContainer::alpOPO()
{
    return alpha3D;
}
