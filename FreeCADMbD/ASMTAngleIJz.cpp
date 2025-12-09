/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTAngleIJz.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJz> ASMTAngleIJz::With()
{
    auto inst = std::make_shared<ASMTAngleIJz>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTAngleIJz::mbdClassNew()
{
    return AngleZIeqcJeqc::With();
}
