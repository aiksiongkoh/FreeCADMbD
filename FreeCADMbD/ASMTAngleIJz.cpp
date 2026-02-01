/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTAngleIJz.h"
#include "AngleZIeqcJeqc.h"
#include "AngleZIecJeqc.h"

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

std::shared_ptr<KinematicIJ> ASMTAngleIJz::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return AngleZIeqcJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> ASMTAngleIJz::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return AngleZIecJeqc::With(frmi, frmj);
}
