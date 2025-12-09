/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Power.h"
#include "Constant.h"
#include "Ln.h"
#include <cassert>
#include "SimulationStoppingError.h"

using namespace MbD;

Power::Power(Symsptr bse, Symsptr ex) : FunctionXY(bse, ex)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Power> Power::With()
{
    auto inst = std::make_shared<Power>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Power> Power::With(Symsptr base, Symsptr exp)
{
    auto inst = std::make_shared<Power>(base, exp);
    inst->initialize();
    return inst;
}

Symsptr Power::differentiateWRTx()
{
    auto yminus1 = Symbolic::sum(y, sptrConstant(-1.0));
    auto power = Symbolic::raisedTo(x, yminus1);
    auto deriv = Symbolic::times(y, power);
    return deriv->simplified(deriv);
}

Symsptr Power::differentiateWRTy()
{
    auto lnterm = std::make_shared<Ln>(x);
    auto deriv = Symbolic::times(clonesptr(), lnterm);
    return deriv->simplified();
}

Symsptr Power::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

double Power::getValue()
{
    return std::pow(x->getValue(), y->getValue());
}
