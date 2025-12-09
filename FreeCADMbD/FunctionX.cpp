/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "FunctionX.h"
#include "Constant.h"
#include "Sum.h"
#include "Arguments.h"
#include "Reciprocal.h"
#include "Integral.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<FunctionX> FunctionX::With()
{
    auto inst = std::make_shared<FunctionX>();
    inst->initialize();
    return inst;
}

void FunctionX::arguments(Symsptr args)
{
    auto arguments = std::static_pointer_cast<Arguments>(args);
    assert(arguments->terms->size() == 1);
    xx = arguments->terms->front();
}

Symsptr FunctionX::copyWith(Symsptr)
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

Symsptr FunctionX::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto itr = std::find_if(set->begin(), set->end(), [sptr](Symsptr sym) {return sptr.get() == sym.get(); });
    if (itr != set->end()) return sptr;
    auto newx = xx->expandUntil(xx, set);
    auto copy = copyWith(newx);
    if (newx->isConstant()) {
        return sptrConstant(copy->getValue());
    }
    else {
        return copy;
    }
}

Symsptr FunctionX::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto itr = std::find_if(set->begin(), set->end(), [sptr](Symsptr sym) {return sptr.get() == sym.get(); });
    if (itr != set->end()) return sptr;
    auto newx = xx->simplifyUntil(xx, set);
    auto copy = copyWith(newx);
    if (newx->isConstant()) {
        return sptrConstant(copy->getValue());
    }
    else {
        return copy;
    }
}

Symsptr FunctionX::differentiateWRT(Symsptr var)
{
    if (this == var.get()) return sptrConstant(1.0);
    auto dfdx = differentiateWRTx();
    auto dxdvar = xx->differentiateWRT(var);
    auto answer = Symbolic::times(dfdx, dxdvar);
    return answer->simplified();
}

Symsptr FunctionX::integrateWRT(Symsptr var)
{
    //Integration is complex. Build up capabilities with time.
    if (this == var.get()) throw SimulationStoppingError("To be implemented.");    //ToDo:
    auto simple = simplified();
    auto answer = std::make_shared<Integral>();
    answer->xx = var;
    answer->integrand = simple;
    if (xx == var) {
        answer->expression = integrateWRTx();
    }
    else {
        auto dxdvar = xx->differentiateWRT(var);
        assert(dxdvar->isConstant());    //ToDo: for other cases.
        auto integdx = integrateWRTx();
        auto reciprocal = std::make_shared<Reciprocal>(dxdvar);
        auto integral = Symbolic::times(integdx, reciprocal);
        answer->expression = integral->simplified();
    }
    return answer;
}

Symsptr FunctionX::differentiateWRTx()
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

Symsptr FunctionX::integrateWRTx()
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

void FunctionX::createMbD()
{
    xx->createMbD();
}

double FunctionX::getValue()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

bool FunctionX::isConstant()
{
    return xx->isConstant();
}
