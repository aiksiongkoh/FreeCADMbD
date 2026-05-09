/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTAngleIJz.h"
#include "AngleZIeqJeq.h"
#include "AngleZIeJeq.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJz> ASMTAngleIJz::With()
{
    auto inst = std::make_shared<ASMTAngleIJz>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> ASMTAngleIJz::mbdClassNew()
{
    return AngleZIeqJeq::With();
}

std::shared_ptr<KinematicIeJe> ASMTAngleIJz::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return AngleZIeqJeq::With(frmi, frmj);
}

std::shared_ptr<KinematicIeJe> ASMTAngleIJz::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return AngleZIeJeq::With(frmi, frmj);
}
