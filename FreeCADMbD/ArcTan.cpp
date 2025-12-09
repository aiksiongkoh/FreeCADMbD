/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ArcTan.h"
#include "SimulationStoppingError.h"

using namespace MbD;

ArcTan::ArcTan(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ArcTan> ArcTan::With()
{
    auto inst = std::make_shared<ArcTan>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ArcTan> ArcTan::With(Symsptr arg)
{
    auto inst = std::make_shared<ArcTan>(arg);
    inst->initialize();
    return inst;
}

double ArcTan::getValue()
{
    return std::atan(xx->getValue());
}

Symsptr ArcTan::copyWith(Symsptr arg)
{
    return ArcTan::With(arg);
}

std::ostream& ArcTan::printOn(std::ostream& s) const
{
    s << "arctan(" << *xx << ")";
    return s;
}
