/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "LogN.h"
#include "SimulationStoppingError.h"

using namespace MbD;

LogN::LogN(Symsptr arg) : FunctionX(arg)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<LogN> LogN::With()
{
    auto inst = std::make_shared<LogN>();
    inst->initialize();
    return inst;
}

std::shared_ptr<LogN> LogN::With(Symsptr arg)
{
    auto inst = std::make_shared<LogN>(arg);
    inst->initialize();
    return inst;
}

double LogN::getValue()
{
    return std::log(xx->getValue());
}

Symsptr LogN::copyWith(Symsptr arg)
{
    return LogN::With(arg);
}

std::ostream& LogN::printOn(std::ostream& s) const
{
    s << "ln(" << *xx << ")";
    return s;
}
