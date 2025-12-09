/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTSpatialItem.h"
#include "Units.h"
#include "Part.h"
#include "ASMTSpatialContainer.h"
#include "EulerAngles.h"

using namespace MbD;

std::shared_ptr<ASMTSpatialItem> ASMTSpatialItem::With()
{
    auto inst = std::make_shared<ASMTSpatialItem>();
    inst->initialize();
    return inst;
}

void ASMTSpatialItem::initialize()
{
    //Do nothing.
}

void ASMTSpatialItem::setPosition3D(FColDsptr vec)
{
    position3D = vec;
}

void ASMTSpatialItem::setQuarternions(double q0, double q1, double q2, double q3)
{
    auto eulerParameters = EulerParameters<double>::With(ListD{ q1, q2, q3, q0 });
    eulerParameters->calc();
    rotationMatrix = eulerParameters->aA;
}

void ASMTSpatialItem::setRotationMatrix(FMatDsptr mat)
{
    rotationMatrix = mat;
}

void ASMTSpatialItem::readPosition3D(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "Position3D");
    std::istringstream iss(lines[0]);
    position3D = FullColumn<double>::With();
    double d;
    while (iss >> d) {
        position3D->push_back(d);
    }
    lines.erase(lines.begin());
}

void ASMTSpatialItem::readRotationMatrix(std::vector<std::string>& lines)
{
    assert(readStringNoSpacesOffTop(lines) == "RotationMatrix");
    rotationMatrix = FullMatrix<double>::With(3, 0);
    for (size_t i = 0; i < 3; i++)
    {
        auto& row = rotationMatrix->at(i);
        std::istringstream iss(lines[0]);
        double d;
        while (iss >> d) {
            row->push_back(d);
        }
        lines.erase(lines.begin());
    }
}

void ASMTSpatialItem::getPosition3D(double& a, double& b, double& c)
{
    a = position3D->at(0);
    b = position3D->at(1);
    c = position3D->at(2);
}

void ASMTSpatialItem::getQuarternions(double& q0, double& q1, double& q2, double& q3)
{
    auto eulerParameters = rotationMatrix->asEulerParameters();
    q0 = eulerParameters->at(3);
    q1 = eulerParameters->at(0);
    q2 = eulerParameters->at(1);
    q3 = eulerParameters->at(2);
}

// Overloads to simplify syntax.
void ASMTSpatialItem::setPosition3D(double a, double b, double c)
{
    position3D = std::make_shared<FullColumn<double>>(ListD{ a, b, c });
}

void ASMTSpatialItem::setRotationMatrix(double v11, double v12, double v13,
    double v21, double v22, double v23,
    double v31, double v32, double v33)
{
    rotationMatrix = FullMatrix<double>::With(ListListD{
        { v11, v12, v13 },
        { v21, v22, v23 },
        { v31, v32, v33 }
        });
}

void ASMTSpatialItem::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelPosition(os, level + 1);
    storeOnLevelRotationMatrix(os, level + 1);
}

void ASMTSpatialItem::storeOnLevelPosition(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "Position3D");
    if (xs == nullptr || xs->empty()) {
        storeOnLevelArray(os, level + 1, *position3D);
    }
    else {
        auto array = getPosition3D(0);
        storeOnLevelArray(os, level + 1, *array);
    }
}

void ASMTSpatialItem::storeOnLevelRotationMatrix(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RotationMatrix");
    if (xs == nullptr || xs->empty()) {
        for (size_t i = 0; i < 3; i++)
        {
            storeOnLevelArray(os, level + 1, *rotationMatrix->at(i));
        }
    }
    else {
        auto rotMat = getRotationMatrix(0);
        for (size_t i = 0; i < 3; i++)
        {
            storeOnLevelArray(os, level + 1, *rotMat->at(i));
        }
    }

}

FColDsptr ASMTSpatialItem::getPosition3D(size_t i)
{
    auto vec3 = std::make_shared<FullColumn<double>>(3);
    if (xs == nullptr || xs->empty()) return vec3;
    vec3->atiput(0, xs->at(i));
    vec3->atiput(1, ys->at(i));
    vec3->atiput(2, zs->at(i));
    return vec3;
}

FMatDsptr ASMTSpatialItem::getRotationMatrix(size_t i)
{
    auto bryantAngles = EulerAngles<double>::With();
    bryantAngles->setRotOrder(1, 2, 3);
    if (bryxs == nullptr || bryxs->empty()) {
        //Do nothing.
    }
    else {
        bryantAngles->at(0) = bryxs->at(i);
        bryantAngles->at(1) = bryys->at(i);
        bryantAngles->at(2) = bryzs->at(i);
    }
    bryantAngles->calc();
    return bryantAngles->aA;
}

FMatDsptr ASMTSpatialItem::aAFf()
{
    return rotationMatrix;
}

FMatDsptr ASMTSpatialItem::aAOf()
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        return ref->aAOf()->timesFullMatrix(aAFf());
    }
    else {
        return aAFf();
    }
}

FColDsptr ASMTSpatialItem::rFfF()
{
    return position3D;
}

FColDsptr ASMTSpatialItem::rOfO()
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        return ref->rOfO()->plusFullColumn(ref->aAOf()->timesFullColumn(rFfF()));
    }
    else {
        return rFfF();
    }
}

FMatDsptr ASMTSpatialItem::aAFf(size_t i)
{
    return getRotationMatrix(i);
}

FMatDsptr ASMTSpatialItem::aAOf(size_t i)
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        return ref->aAOf(i)->timesFullMatrix(aAFf(i));
    }
    else {
        return aAFf(i);
    }
}

FColDsptr ASMTSpatialItem::rFfF(size_t i)
{
    return getPosition3D(i);
}

FColDsptr ASMTSpatialItem::rOfO(size_t i)
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        return ref->rOfO(i)->plusFullColumn(ref->aAOf(i)->timesFullColumn(rFfF(i)));
    }
    else {
        return rFfF(i);
    }
}

FColDsptr ASMTSpatialItem::vFfF(size_t i)
{
    return FullColumn<double>::With(3);
}

FColDsptr ASMTSpatialItem::vOfO(size_t i)
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        auto term1 = ref->vOfO(i);
        auto term2 = ref->omeOfO(i)->cross(rFfF(i));
        auto term3 = vFfF(i);
        return term1->plusFullColumn(term2)->plusFullColumn(term3);
    }
    else {
        return vFfF(i);
    }
}

FColDsptr ASMTSpatialItem::omeFfF(size_t i)
{
    return FullColumn<double>::With(3);
}

FColDsptr ASMTSpatialItem::omeOfO(size_t i)
{
    if (owner) {
        auto ref = static_cast<ASMTSpatialItem*>(owner);
        return ref->omeOfO(i)->plusFullColumn(omeFfF(i));
    }
    else {
        return omeFfF(i);
    }
}
