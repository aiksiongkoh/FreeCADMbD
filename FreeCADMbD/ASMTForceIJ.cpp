/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceIJ.h"
#include "Units.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTForceIJ> ASMTForceIJ::With()
{
    auto inst = std::make_shared<ASMTForceIJ>();
    inst->initialize();
    return inst;
}

void ASMTForceIJ::createMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

double ASMTForceIJ::asmtUnit()
{
    return asmtUnits()->force;
}
