/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTMarkerTemp.h"
#include <cassert>
#include "FullMatrix.h"
#include "ASMTAssembly.h"
#include "Numeric.h"
#include "Part.h"
#include "PartFrame.h"
#include "MarkerFrameq.h"

#include <sstream>

using namespace MbD;

std::shared_ptr<ASMTMarkerTemp> ASMTMarkerTemp::With()
{
    auto inst = std::make_shared<ASMTMarkerTemp>();
    inst->initialize();
    return inst;
}

void ASMTMarkerTemp::initialize()
{
    name = "MassMarker";
}

void ASMTMarkerTemp::parseASMT(std::vector<std::string>& lines)
{
    size_t pos = lines[0].find_first_not_of("\t");
    auto leadingTabs = lines[0].substr(0, pos);
    assert(lines[0] == (leadingTabs + "Name"));
    lines.erase(lines.begin());
    name = readStringNoSpacesOffTop(lines);
    assert(lines[0] == (leadingTabs + "Position3D"));
    lines.erase(lines.begin());
    position3D = readColumnOfDoubles(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "RotationMatrix"));
    lines.erase(lines.begin());
    rotationMatrix = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        auto row = readRowOfDoubles(lines[0]);
        rotationMatrix->atiput(i, row);
        lines.erase(lines.begin());
    }
    assert(lines[0] == (leadingTabs + "Mass"));
    lines.erase(lines.begin());
    mass = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "MomentOfInertias"));
    lines.erase(lines.begin());
    momentOfInertias = DiagonalMatrix<double>::With(3);
    auto row = readRowOfDoubles(lines[0]);
    lines.erase(lines.begin());
    for (size_t i = 0; i < 3; i++)
    {
        momentOfInertias->atiput(i, row->at(i));
    }
    assert(lines[0] == (leadingTabs + "Density"));
    lines.erase(lines.begin());
    density = readDouble(lines[0]);
    lines.erase(lines.begin());
}

void ASMTMarkerTemp::setMass(double m)
{
    mass = m;
}

void ASMTMarkerTemp::setDensity(double rho)
{
    density = rho;
}

void ASMTMarkerTemp::setMomentOfInertias(DiagMatDsptr mat)
{
    momentOfInertias = mat;
}

void ASMTMarkerTemp::createMbD()
{
    //ASMTPart contains ASMTRefPoint contains ASMTMarker
    //PartFrame contains MarkerFrame contains EndFrame
    auto asmtPrt = dynamic_cast<ASMTPart*>(partOrAssembly());
    auto prt = std::static_pointer_cast<Part>(asmtPrt->mbdObject);
    auto prtfrm = prt->partFrame;
    auto mkr = MarkerFrameq::With(name.c_str());
    auto efrm = EndFrameq::With();
    prtfrm->addMarkerFrame(mkr);
    mkr->rpmp = rpmp()->times(asmtUnits()->length);
    mkr->aApm = aApm();
    mkr->addEndFrame(efrm);
    mbdObject = efrm;
}

FColDsptr ASMTMarkerTemp::rpmp()
{
    //p is center of mass
    return FullColumn<double>::With(3, 0.0);
}

FMatDsptr ASMTMarkerTemp::aApm()
{
    return rotationMatrix;
}

// Overloads to simplify syntax.
void ASMTMarkerTemp::setMomentOfInertias(double a, double b, double c)
{
    momentOfInertias = DiagonalMatrix<double>::With(ListD{ a, b, c });
}

void ASMTMarkerTemp::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "PrincipalMassMarker");
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTSpatialItem::storeOnLevel(os, level);
    storeOnLevelString(os, level + 1, "Mass");
    storeOnLevelDouble(os, level + 2, mass);
    storeOnLevelString(os, level + 1, "MomentOfInertias");
    storeOnLevelArray(os, level + 2, *momentOfInertias);
    storeOnLevelString(os, level + 1, "Density");
    storeOnLevelDouble(os, level + 2, density);
}

void ASMTMarkerTemp::zeroMass()
{
    mass = 0.0;
    density = 0.0;
    momentOfInertias = DiagonalMatrix<double>::With(ListD{ 0.0, 0.0, 0.0 });
}

std::string ASMTMarkerTemp::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTSpatialItem::reportComparisonWith(otherItem);
    if (!report.empty()) {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTMarkerTemp>(otherItem);
    if (!other) {
        return fullName("") + " comparison item is not an ASMTMarkerTemp.\n";
    }
    if (!Numeric::equaltol(mass, other->mass, 1.0e-9)) {
        std::ostringstream stream;
        stream << fullName("") << " mass " << mass << " != " << other->mass << "\n";
        return stream.str();
    }
    if (!Numeric::equaltol(density, other->density, 1.0e-9)) {
        std::ostringstream stream;
        stream << fullName("") << " density " << density << " != " << other->density << "\n";
        return stream.str();
    }
    if (!momentOfInertias && other->momentOfInertias) {
        return fullName("") + " missing momentOfInertias.\n";
    }
    if (momentOfInertias && !other->momentOfInertias) {
        return fullName("") + " missing comparison momentOfInertias.\n";
    }
    if (momentOfInertias && other->momentOfInertias && !momentOfInertias->equaltol(other->momentOfInertias, 1.0e-9)) {
        std::ostringstream stream;
        stream << fullName("") << " momentOfInertias " << *momentOfInertias << " != " << *other->momentOfInertias << "\n";
        return stream.str();
    }
    return std::string{};
}
