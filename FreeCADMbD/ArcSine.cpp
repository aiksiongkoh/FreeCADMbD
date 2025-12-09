/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ArcSine.h"
#include "SimulationStoppingError.h"

using namespace MbD;

ArcSine::ArcSine(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ArcSine> ArcSine::With()
{
    auto inst = std::make_shared<ArcSine>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ArcSine> ArcSine::With(Symsptr arg)
{
    auto inst = std::make_shared<ArcSine>(arg);
    inst->initialize();
    return inst;
}

double ArcSine::getValue()
{
    return std::asin(xx->getValue());
}

Symsptr ArcSine::copyWith(Symsptr arg)
{
    return ArcSine::With(arg);
}

std::ostream& ArcSine::printOn(std::ostream& s) const
{
    s << "arcsin(" << *xx << ")";
    return s;
}
