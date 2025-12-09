/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTdAngleIJy.h"
#include "DAngleYIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTdAngleIJy> ASMTdAngleIJy::With()
{
    auto inst = std::make_shared<ASMTdAngleIJy>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTdAngleIJy::mbdClassNew()
{
    return DAngleYIeqcJeqc::With();
}
