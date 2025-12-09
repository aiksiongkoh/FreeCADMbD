/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Negative.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<Negative> Negative::With(Symsptr arg)
{
    auto sym = std::make_shared<Negative>(arg);
    sym->initialize();
    return sym;
}

double Negative::getValue()
{
    return -xx->getValue();
}

Symsptr Negative::differentiateWRTx()
{
    return sptrConstant(-1);
}

Symsptr Negative::integrateWRTx()
{
    return Negative::With(xx);
}

Symsptr Negative::expandUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto expand = xx->expandUntil(xx, set);
    return Negative::With(expand);
}

Symsptr Negative::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto simple = xx->simplifyUntil(xx, set);
    if (simple->isConstant()) {
        return sptrConstant(-simple->getValue());
    }
    return Negative::With(simple);
}

Symsptr Negative::copyWith(Symsptr arg)
{
    return Negative::With(arg);
}

Symsptr Negative::clonesptr()
{
    return std::make_shared<Negative>(*this);
}

std::ostream& Negative::printOn(std::ostream& s) const
{
    s << "-(" << *xx << ")";
    return s;
}
