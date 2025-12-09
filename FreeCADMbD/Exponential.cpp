/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Exponential.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Exponential::Exponential(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Exponential> Exponential::With()
{
    auto inst = std::make_shared<Exponential>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Exponential> Exponential::With(Symsptr arg)
{
    auto inst = std::make_shared<Exponential>(arg);
    inst->initialize();
    return inst;
}

double Exponential::getValue()
{
    return std::log(xx->getValue());
}

Symsptr Exponential::copyWith(Symsptr arg)
{
    return Exponential::With(arg);
}

std::ostream& Exponential::printOn(std::ostream& s) const
{
    s << "exp(" << *xx << ")";
    return s;
}
