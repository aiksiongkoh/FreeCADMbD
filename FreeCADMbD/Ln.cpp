/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Ln.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Ln::Ln(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Ln> Ln::With()
{
    auto inst = std::make_shared<Ln>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Ln> Ln::With(Symsptr arg)
{
    auto inst = std::make_shared<Ln>(arg);
    inst->initialize();
    return inst;
}

double Ln::getValue()
{
    return std::log(xx->getValue());
}

Symsptr Ln::copyWith(Symsptr arg)
{
    return Ln::With(arg);
}
