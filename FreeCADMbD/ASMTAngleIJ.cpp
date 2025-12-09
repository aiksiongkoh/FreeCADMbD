/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTAngleIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJ> ASMTAngleIJ::With()
{
    auto inst = std::make_shared<ASMTAngleIJ>();
    inst->initialize();
    return inst;
}

double ASMTAngleIJ::asmtUnit()
{
    return asmtUnits()->angle;
}
