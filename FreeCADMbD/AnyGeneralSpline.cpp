/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AnyGeneralSpline.h"
#include "SimulationStoppingError.h"

using namespace MbD;

AnyGeneralSpline::AnyGeneralSpline(Symsptr arg) : FunctionFromData(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<AnyGeneralSpline> AnyGeneralSpline::With()
{
    auto inst = std::make_shared<AnyGeneralSpline>();
    inst->initialize();
    return inst;
}
