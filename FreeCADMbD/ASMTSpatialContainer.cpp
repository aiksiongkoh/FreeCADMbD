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
#include "ASMTRefPoint.h"
#include "ASMTRefCurve.h"
#include "ASMTRefSurface.h"
#include "ASMTMarker.h"
#include "ASMTMarkerTemp.h"
#include "Units.h"
#include "Part.h"
#include "System.h"
#include "PosVelAccData.h"
#include "SimulationStoppingError.h"
#include "EulerAngles.h"

using namespace MbD;

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

void ASMTSpatialContainer::readRefPoints(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "RefPoints");
    refPoints->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("RefCurves") != std::string::npos; });
    std::vector<std::string> refPointsLines(lines.begin(), it);
    while (!refPointsLines.empty())
    {
        readRefPoint(refPointsLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefPoint(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "RefPoint");
    auto refPoint = ASMTRefPoint::With();
    refPoint->owner = this;
    refPoint->parseASMT(lines);
    refPoints->push_back(refPoint);
}

void ASMTSpatialContainer::readRefCurves(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "RefCurves");
    refCurves->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("RefSurfaces") != std::string::npos; });
    std::vector<std::string> refCurvesLines(lines.begin(), it);
    while (!refCurvesLines.empty())
    {
        readRefCurve(refCurvesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefCurve(std::vector<std::string> &)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSpatialContainer::readRefSurfaces(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "RefSurfaces");
    refSurfaces->clear();
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("Part") != std::string::npos; });
    std::vector<std::string> refSurfacesLines(lines.begin(), it);
    while (!refSurfacesLines.empty())
    {
        readRefSurface(refSurfacesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTSpatialContainer::readRefSurface(std::vector<std::string> &)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSpatialContainer::readXs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "X", inxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readYs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Y", inys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readZs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Z", inzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantxs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryantx", inbryxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantys(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryanty", inbryys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readBryantzs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "Bryantz", inbryzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVXs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VX", invxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVYs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VY", invys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readVZs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "VZ", invzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaXs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaX", inomexs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaYs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaY", inomeys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmegaZs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "OmegaZ", inomezs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAXs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AX", inaxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAYs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AY", inays);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAZs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AZ", inazs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaXs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaX", inalpxs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaYs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaY", inalpys);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readAlphaZs(std::vector<std::string> &lines)
{
    std::string str = lines[0];
    readDoublesInto(str, "AlphaZ", inalpzs);
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::createMbD()
{
    for (auto refPoint : *refPoints)
    {
        refPoint->createMbD();
    }
    for (auto refCurve : *refCurves)
    {
        refCurve->createMbD();
    }
    for (auto refSurface : *refSurfaces)
    {
        refSurface->createMbD();
    }
}

FColDsptr ASMTSpatialContainer::omeOpO()
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

ASMTSpatialContainer *ASMTSpatialContainer::partOrAssembly()
{
    return this;
}

void ASMTSpatialContainer::updateFromMbD()
{
    auto zero = FullColumn<double>::With(3, 0.0);
    auto identityMat = FullMatrix<double>::With(ListListD{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}});
    auto rOcmO = zero;
    auto aAOp = identityMat;
    auto vOcmO = zero;
    auto omeOPO = zero;
    omega3D = omeOPO;
    auto aOcmO = zero;
    auto alpOPO = zero;
    alpha3D = alpOPO;
    auto rPcmP = zero;
    auto aAPp = identityMat;
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

void ASMTSpatialContainer::compareResults(AnalysisType type)
{
    if (inxs == nullptr || inxs->empty())
        return;
    auto lambda = [&](std::string name, FRowDsptr vals, FRowDsptr invals, size_t i, size_t nSig, double tol)
    {
        auto val = vals->at(i);
        auto inval = invals->at(i);
        auto tol2 = tol / 10.0;
        if (name.find("bry") != std::string::npos)
        {
            if (Numeric::anglesEqual(val, inval, tol2))
                return;
        }
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
    auto lengthTol = mbdUnts->length * factor;
    auto angleTol = mbdUnts->angle * factor;
    auto velocityTol = mbdUnts->velocity * factor;
    auto omegaTol = mbdUnts->omega * factor;
    auto accelerationTol = mbdUnts->acceleration * factor;
    auto alphaTol = mbdUnts->alpha * factor;
    auto i = xs->size() - 1;
    // Pos
    lambda("xs", xs, inxs, i, nDigit, lengthTol);
    lambda("ys", ys, inys, i, nDigit, lengthTol);
    lambda("zs", zs, inzs, i, nDigit, lengthTol);
    lambda("bryxs", bryxs, inbryxs, i, nDigit, angleTol);
    lambda("bryys", bryys, inbryys, i, nDigit, angleTol);
    lambda("bryzs", bryzs, inbryzs, i, nDigit, angleTol);
    // Vel
    lambda("vxs", vxs, invxs, i, nDigit, velocityTol);
    lambda("vys", vys, invys, i, nDigit, velocityTol);
    lambda("vzs", vzs, invzs, i, nDigit, velocityTol);
    lambda("omexs", omexs, inomexs, i, nDigit, omegaTol);
    lambda("omeys", omeys, inomeys, i, nDigit, omegaTol);
    lambda("omezs", omezs, inomezs, i, nDigit, omegaTol);
    // Acc
    if (type == AnalysisType::INPUT)
        return;
    lambda("axs", axs, inaxs, i, nDigit, accelerationTol);
    lambda("ays", ays, inays, i, nDigit, accelerationTol);
    lambda("azs", azs, inazs, i, nDigit, accelerationTol);
    lambda("alpxs", alpxs, inalpxs, i, nDigit, alphaTol);
    lambda("alpys", alpys, inalpys, i, nDigit, alphaTol);
    lambda("alpzs", alpzs, inalpzs, i, nDigit, alphaTol);
}

void ASMTSpatialContainer::compareResults2(AnalysisType type)
{
    if (dataSeries == nullptr || dataSeries->empty() || dataSeriesIn == nullptr || dataSeriesIn->empty())
        return;
    auto lambda = [&](std::string name, size_t i, FColDsptr col, FColDsptr incol, size_t nSig, double tol)
    {
        auto val = col->at(i);
        auto inval = incol->at(i);
        auto tol2 = tol / 10.0;
        if (name.find("bry") != std::string::npos)
        {
            if (Numeric::anglesEqual(val, inval, tol2))
                return;
        }
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
    auto lengthTol = mbdUnts->length * factor;
    auto angleTol = mbdUnts->angle * factor;
    auto velocityTol = mbdUnts->velocity * factor;
    auto omegaTol = mbdUnts->omega * factor;
    auto accelerationTol = mbdUnts->acceleration * factor;
    auto alphaTol = mbdUnts->alpha * factor;
    auto i = dataSeries->size() - 1;
    auto data = std::dynamic_pointer_cast<PosVelAccData>(dataSeries->at(i));
    auto dataIn = std::dynamic_pointer_cast<PosVelAccData>(dataSeriesIn->at(i));
    if (data == nullptr || dataIn == nullptr)
        return;

    // Pos
    lambda("xs", 0, data->rFfF, dataIn->rFfF, nDigit, lengthTol);
    lambda("ys", 1, data->rFfF, dataIn->rFfF, nDigit, lengthTol);
    lambda("zs", 2, data->rFfF, dataIn->rFfF, nDigit, lengthTol);
    lambda("bryxs", 0, data->bryAngFf, dataIn->bryAngFf, nDigit, angleTol);
    lambda("bryys", 1, data->bryAngFf, dataIn->bryAngFf, nDigit, angleTol);
    lambda("bryzs", 2, data->bryAngFf, dataIn->bryAngFf, nDigit, angleTol);
    // Vel
    lambda("vxs", 0, data->vFfF, dataIn->vFfF, nDigit, velocityTol);
    lambda("vys", 1, data->vFfF, dataIn->vFfF, nDigit, velocityTol);
    lambda("vzs", 2, data->vFfF, dataIn->vFfF, nDigit, velocityTol);
    lambda("omexs", 0, data->omeFfF, dataIn->omeFfF, nDigit, omegaTol);
    lambda("omeys", 1, data->omeFfF, dataIn->omeFfF, nDigit, omegaTol);
    lambda("omezs", 2, data->omeFfF, dataIn->omeFfF, nDigit, omegaTol);
    // Acc
    if (type == AnalysisType::INPUT)
        return;
    lambda("axs", 0, data->aFfF, dataIn->aFfF, nDigit, accelerationTol);
    lambda("ays", 1, data->aFfF, dataIn->aFfF, nDigit, accelerationTol);
    lambda("azs", 2, data->aFfF, dataIn->aFfF, nDigit, accelerationTol);
    lambda("alpxs", 0, data->alpFfF, dataIn->alpFfF, nDigit, alphaTol);
    lambda("alpys", 1, data->alpFfF, dataIn->alpFfF, nDigit, alphaTol);
    lambda("alpzs", 2, data->alpFfF, dataIn->alpFfF, nDigit, alphaTol);
}

void ASMTSpatialContainer::outputResults(AnalysisType)
{
    if (inxs != nullptr && !inxs->empty())
        return;
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
    for (auto mkr : *aItemList)
    {
        markerNames.push_back(mkr->name);
    }
    std::stringstream ss;
    auto count = 0;
    while (true)
    {
        ss.str("");
        ss << "Marker";
        ss << count;
        if (std::find(markerNames.begin(), markerNames.end(), ss.str()) == markerNames.end())
            break;
        count++;
    }
    return ss.str();
}

std::shared_ptr<std::vector<std::shared_ptr<ASMTMarker>>> ASMTSpatialContainer::markerList() const
{
    auto markers = std::make_shared<std::vector<std::shared_ptr<ASMTMarker>>>();
    for (auto refPoint : *refPoints)
    {
        auto refmarkers = refPoint->markers;
        markers->insert(markers->end(), refmarkers->begin(), refmarkers->end());
    }
    return markers;
}

void ASMTSpatialContainer::storeOnLevel(std::ofstream &os, size_t level)
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

void ASMTSpatialContainer::readVelocity3D(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "Velocity3D");
    std::istringstream iss(lines[0]);
    velocity3D = FullColumn<double>::With();
    double d;
    while (iss >> d)
    {
        velocity3D->push_back(d);
    }
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::readOmega3D(std::vector<std::string> &lines)
{
    readStringNoSpacesOffTopEqualOrThrow(lines, "Omega3D");
    std::istringstream iss(lines[0]);
    omega3D = FullColumn<double>::With();
    double d;
    while (iss >> d)
    {
        omega3D->push_back(d);
    }
    lines.erase(lines.begin());
}

void ASMTSpatialContainer::setVelocity3D(double a, double b, double c)
{
    velocity3D = std::make_shared<FullColumn<double>>(ListD{a, b, c});
}

void ASMTSpatialContainer::setOmega3D(double a, double b, double c)
{
    omega3D = std::make_shared<FullColumn<double>>(ListD{a, b, c});
}

void ASMTSpatialContainer::storeOnLevelVelocity(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Velocity3D");
    if (vxs == nullptr || vxs->empty())
    {
        storeOnLevelArray(os, level + 1, *velocity3D);
    }
    else
    {
        auto array = getVelocity3D(0);
        storeOnLevelArray(os, level + 1, *array);
    }
}

void ASMTSpatialContainer::storeOnLevelOmega(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Omega3D");
    if (omexs == nullptr || omexs->empty())
    {
        storeOnLevelArray(os, level + 1, *omega3D);
    }
    else
    {
        auto array = getOmega3D(0);
        storeOnLevelArray(os, level + 1, *array);
    }
}

void ASMTSpatialContainer::storeOnLevelRefPoints(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "RefPoints");
    for (auto refPoint : *refPoints)
    {
        refPoint->storeOnLevel(os, level + 1);
    }
}

void ASMTSpatialContainer::storeOnLevelRefCurves(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "RefCurves");
    for (auto refCurve : *refCurves)
    {
        refCurve->storeOnLevel(os, level);
    }
}

void ASMTSpatialContainer::storeOnLevelRefSurfaces(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "RefSurfaces");
    for (auto refSurface : *refSurfaces)
    {
        refSurface->storeOnLevel(os, level);
    }
}

void ASMTSpatialContainer::storeOnTimeSeries(std::ofstream &os)
{
    storeOnArray(os, "X", xs);
    storeOnArray(os, "Y", ys);
    storeOnArray(os, "Z", zs);
    storeOnArray(os, "Bryantx", bryxs);
    storeOnArray(os, "Bryanty", bryys);
    storeOnArray(os, "Bryantz", bryzs);
    storeOnArray(os, "VX", vxs);
    storeOnArray(os, "VY", vys);
    storeOnArray(os, "VZ", vzs);
    storeOnArray(os, "OmegaX", omexs);
    storeOnArray(os, "OmegaY", omeys);
    storeOnArray(os, "OmegaZ", omezs);
    storeOnArray(os, "AX", axs);
    storeOnArray(os, "AY", ays);
    storeOnArray(os, "AZ", azs);
    storeOnArray(os, "AlphaX", alpxs);
    storeOnArray(os, "AlphaY", alpys);
    storeOnArray(os, "AlphaZ", alpzs);
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
    for (auto refPoint : *refPoints)
    {
        refPoint->updateFromInputState();
    }
}

std::shared_ptr<StateData> ASMTSpatialContainer::dataFromMbD()
{
    //"
    // P := part frame.
    // p := principal frame at cm.
    // rOcmO := rOPO + aAOP*rPcmP.
    // aAOp := aAOP*aAPp.
    // vOcmO := vOPO + aAdotOP*rPcmP
    //:= vOPO + (omeOPO cross: aAOP*rPcmP).
    // omeOpO := omeOPO.
    // aOcmO := aOPO + aAddotOP*rPcmP
    //:= aOPO + (alpOPO cross: aAOP*rPcmP) + (omeOPO cross: (omeOPO cross: aAOP*rPcmP)).
    // alpOpO := alpOPO.
    //
    // Therefore
    // aAOP := aAOp*aAPpT
    // rOPO := rOcmO - aAOP*rPcmP.
    // omeOPO := omeOpO.
    // vOPO    := vOcmO - (omeOPO cross: aAOP*rPcmP).
    // alpOPO := alpOpO.
    // aOPO    := aOcmO - (alpOPO cross: aAOP*rPcmP) - (omeOPO cross: (omeOPO cross:
    // aAOP*rPcmP)).
    //"
    throw SimulationStoppingError("Subclass to implement.");
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
