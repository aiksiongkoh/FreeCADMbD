/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTRefPoint.h"
#include "ASMTMarker.h"

using namespace MbD;

std::shared_ptr<ASMTRefPoint> ASMTRefPoint::With()
{
    auto inst = std::make_shared<ASMTRefPoint>();
    inst->initialize();
    return inst;
}

void ASMTRefPoint::parseASMT(std::vector<std::string>& lines)
{
    readPosition3D(lines);
    readRotationMatrix(lines);
    readMarkers(lines);
}

std::string ASMTRefPoint::fullName(const std::string& partialName)
{
    return owner->fullName(partialName);
}

void ASMTRefPoint::createMbD()
{
    for (auto& marker : *markers) {
        marker->createMbD();
    }
}

void ASMTRefPoint::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "RefPoint");
    ASMTSpatialItem::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "Markers");
    for (auto& marker : *markers) {
        marker->storeOnLevel(os, level + 2);
    }
}
