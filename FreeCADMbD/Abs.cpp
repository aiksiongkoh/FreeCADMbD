/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Abs.h"

using namespace MbD;

Abs::Abs(Symsptr arg) : FunctionX(arg)
{
    //Do nothing.
}

std::shared_ptr<Abs> Abs::With()
{
    auto inst = std::make_shared<Abs>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Abs> Abs::With(Symsptr arg)
{
    auto inst = std::make_shared<Abs>(arg);
    inst->initialize();
    return inst;
}

double Abs::getValue()
{
    return std::abs(xx->getValue());
}

Symsptr Abs::copyWith(Symsptr arg)
{
    return Abs::With(arg);
}

std::ostream& Abs::printOn(std::ostream& s) const
{
    s << "abs(" << *xx << ")";
    return s;
}
