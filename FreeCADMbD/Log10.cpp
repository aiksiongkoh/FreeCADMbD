/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Log10.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Log10::Log10(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Log10> Log10::With()
{
    auto inst = std::make_shared<Log10>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Log10> Log10::With(Symsptr arg)
{
    auto inst = std::make_shared<Log10>(arg);
    inst->initialize();
    return inst;
}

double Log10::getValue()
{
    return std::log(xx->getValue());
}

Symsptr Log10::copyWith(Symsptr arg)
{
    return Log10::With(arg);
}

std::ostream& Log10::printOn(std::ostream& s) const
{
    s << "lg(" << *xx << ")";
    return s;
}
