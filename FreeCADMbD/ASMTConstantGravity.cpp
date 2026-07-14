/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTConstantGravity.h"
#include "ASMTAssembly.h"
#include "Units.h"
#include "ConstantGravity.h"
#include "System.h"
#include "Part.h"

#include <sstream>

using namespace MbD;

std::shared_ptr<ASMTConstantGravity> ASMTConstantGravity::With()
{
    auto inst = std::make_shared<ASMTConstantGravity>();
    inst->initialize();
    return inst;
}

void ASMTConstantGravity::initialize()
{
    //Do nothing.
}

void ASMTConstantGravity::parseASMT(std::vector<std::string>& lines)
{
    g = readColumnOfDoubles(lines[0]);
    lines.erase(lines.begin());
}

void ASMTConstantGravity::createMbD()
{
    auto mbdGravity = ConstantGravity::With();
    mbdObject = mbdGravity;
    mbdGravity->gXYZ = g->times(asmtUnits()->acceleration);
    mbdSys()->addGravity(mbdGravity);
}

FColDsptr ASMTConstantGravity::getg() const
{
    return g;
}

void ASMTConstantGravity::setg(FColDsptr gravity)
{
    g = gravity;
}

void ASMTConstantGravity::setg(double a, double b, double c)
{
    g = std::make_shared<FullColumn<double>>(ListD{ a, b, c });
}

void ASMTConstantGravity::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "ConstantGravity");
    storeOnLevelArray(os, level + 1, *g);
}

std::string ASMTConstantGravity::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTItem::reportComparisonWith(otherItem);
    if (!report.empty()) {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTConstantGravity>(otherItem);
    if (!other) {
        return fullName("") + " comparison item is not an ASMTConstantGravity.\n";
    }
    if (!g && other->g) {
        return fullName("") + " missing g.\n";
    }
    if (g && !other->g) {
        return fullName("") + " missing comparison g.\n";
    }
    if (g && other->g && !g->equaltol(other->g, 1.0e-9)) {
        std::ostringstream stream;
        stream << fullName("") << " g " << *g << " != " << *other->g << "\n";
        return stream.str();
    }
    return std::string{};
}
