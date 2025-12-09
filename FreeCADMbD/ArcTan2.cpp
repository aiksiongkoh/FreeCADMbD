/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ArcTan2.h"
#include "SimulationStoppingError.h"

using namespace MbD;

ArcTan2::ArcTan2(Symsptr arg, Symsptr arg1) : FunctionXY(arg, arg1)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ArcTan2> ArcTan2::With()
{
    auto inst = std::make_shared<ArcTan2>();
    inst->initialize();
    return inst;
}

double ArcTan2::getValue()
{
    return std::atan2(y->getValue(), x->getValue());
}

Symsptr ArcTan2::differentiateWRTx()
{
    return Symsptr();
}

Symsptr ArcTan2::differentiateWRTy()
{
    return Symsptr();
}
