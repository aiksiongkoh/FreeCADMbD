/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTRefSurface.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTRefSurface> ASMTRefSurface::With()
{
    auto inst = std::make_shared<ASMTRefSurface>();
    inst->initialize();
    return inst;
}

void ASMTRefSurface::parseASMT(std::vector<std::string>&)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTRefSurface::storeOnLevel(std::ofstream&, size_t)
{
    throw SimulationStoppingError("To be implemented.");
}
