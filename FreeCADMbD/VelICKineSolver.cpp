/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "VelICKineSolver.h"

using namespace MbD;

std::shared_ptr<VelICKineSolver> VelICKineSolver::With()
{
    auto inst = std::make_shared<VelICKineSolver>();
    inst->initialize();
    return inst;
}
