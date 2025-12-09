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
