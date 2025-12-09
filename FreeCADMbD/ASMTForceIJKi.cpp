/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTForceIJKi> ASMTForceIJKi::With()
{
    auto inst = std::make_shared<ASMTForceIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTForceIJKi::mbdClassNew()
{
    return std::shared_ptr<KinematicIJ>();
}

double ASMTForceIJKi::asmtUnit()
{
    return asmtUnits()->force;
}
