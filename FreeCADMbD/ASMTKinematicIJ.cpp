/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTKinematicIJ.h"

using namespace MbD;

std::shared_ptr<ASMTKinematicIJ> ASMTKinematicIJ::With()
{
    auto inst = std::make_shared<ASMTKinematicIJ>();
    inst->initialize();
    return inst;
}
