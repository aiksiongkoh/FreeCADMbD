/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Reciprocal.h"
#include "Negative.h"
#include "Power.h"
#include "Constant.h"
#include "Ln.h"

using namespace MbD;

std::shared_ptr<Reciprocal> Reciprocal::With()
{
    auto inst = std::make_shared<Reciprocal>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Reciprocal> Reciprocal::With(Symsptr arg)
{
    auto inst = std::make_shared<Reciprocal>(arg);
    inst->initialize();
    return inst;
}

double Reciprocal::getValue()
{
    return 1.0 / xx->getValue();
}

Symsptr Reciprocal::differentiateWRTx()
{
    auto mtwo = sptrConstant(-2);
    auto sq = std::make_shared<Power>(xx, mtwo);
    return Negative::With(sq);
}

Symsptr Reciprocal::integrateWRTx()
{
    return Ln::With(xx);
}

Symsptr Reciprocal::copyWith(Symsptr arg)
{
    return Reciprocal::With(arg);
}

std::ostream& Reciprocal::printOn(std::ostream& s) const
{
    s << "/(" << *xx << ")";
    return s;
}
