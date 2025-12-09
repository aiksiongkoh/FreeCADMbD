/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTRefCurve.h"

using namespace MbD;

std::shared_ptr<ASMTRefCurve> ASMTRefCurve::With()
{
    auto inst = std::make_shared<ASMTRefCurve>();
    inst->initialize();
    return inst;
}

void ASMTRefCurve::parseASMT(std::vector<std::string>&)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTRefCurve::storeOnLevel(std::ofstream&, size_t)
{
    throw SimulationStoppingError("To be implemented.");
}
