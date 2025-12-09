/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Sine.h"
#include "Cosine.h"

using namespace MbD;

std::shared_ptr<Sine> Sine::With()
{
    auto inst = std::make_shared<Sine>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Sine> Sine::With(Symsptr arg)
{
    auto inst = std::make_shared<Sine>(arg);
    inst->initialize();
    return inst;
}

double Sine::getValue()
{
    return std::sin(xx->getValue());
}

Symsptr Sine::differentiateWRTx()
{
    return Cosine::With(xx);
}

Symsptr Sine::copyWith(Symsptr arg)
{
    return Sine::With(arg);
}

Symsptr Sine::clonesptr()
{
    return std::make_shared<Sine>(*this);
}

Symsptr Sine::integrateWRTx()
{
    return Cosine::With(xx);
}

std::ostream& Sine::printOn(std::ostream& s) const
{
    s << "sin(" << *xx << ")";
    return s;
}
