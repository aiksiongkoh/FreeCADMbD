/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTdAngleIJx.h"
#include "DAngleXIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTdAngleIJx> ASMTdAngleIJx::With()
{
    auto inst = std::make_shared<ASMTdAngleIJx>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTdAngleIJx::mbdClassNew()
{
    return DAngleXIeqcJeqc::With();
}
