/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTExtrusion.h"

using namespace MbD;

std::shared_ptr<ASMTExtrusion> ASMTExtrusion::With()
{
    auto inst = std::make_shared<ASMTExtrusion>();
    inst->initialize();
    return inst;
}
