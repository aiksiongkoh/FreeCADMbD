/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "PiecewiseFunction.h"
#include "Integral.h"

using namespace MbD;

PiecewiseFunction::PiecewiseFunction(Symsptr var, std::shared_ptr<std::vector<Symsptr>> funcs, std::shared_ptr<std::vector<Symsptr>> trans)
{
    assert(var);
    assert(functions->empty());
    xx = var;
    functions->clear();
    functions->insert(functions->end(), funcs->begin(), funcs->end());
    transitions->clear();
    transitions->insert(transitions->end(), trans->begin(), trans->end());
}

std::shared_ptr<PiecewiseFunction> PiecewiseFunction::With()
{
    auto inst = std::make_shared<PiecewiseFunction>();
    inst->initialize();
    return inst;
}

std::shared_ptr<PiecewiseFunction> PiecewiseFunction::With(Symsptr var, std::shared_ptr<std::vector<Symsptr>> funcs, std::shared_ptr<std::vector<Symsptr>> trans)
{
    auto inst = std::make_shared<PiecewiseFunction>(var, funcs, trans);
    inst->initialize();
    return inst;
}

Symsptr PiecewiseFunction::expandUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto expansions = std::make_shared<std::vector<Symsptr>>(functions->size());
    std::transform(functions->begin(),
        functions->end(),
        expansions->begin(),
        [&](auto& func) { return func->expandUntil(func, set); }
    );
    return PiecewiseFunction::With(xx, expansions, transitions);
}

Symsptr PiecewiseFunction::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto simplifications = std::make_shared<std::vector<Symsptr>>(functions->size());
    std::transform(functions->begin(),
        functions->end(),
        simplifications->begin(),
        [&](auto& func) { return func->simplifyUntil(func, set); }
    );
    return PiecewiseFunction::With(xx, simplifications, transitions);
}

Symsptr PiecewiseFunction::differentiateWRTx()
{
    auto derivatives = std::make_shared<std::vector<Symsptr>>(functions->size());
    std::transform(functions->begin(),
        functions->end(),
        derivatives->begin(),
        [&](auto& func) { return func->differentiateWRT(xx); }
    );
    return PiecewiseFunction::With(xx, derivatives, transitions);
}

Symsptr PiecewiseFunction::integrateWRT(Symsptr var)
{
    assert(xx == var);
    auto simple = simplified();
    auto answer = std::make_shared<Integral>();
    answer->xx = var;
    answer->integrand = simple;
    auto integrals = std::make_shared<std::vector<Symsptr>>();
    for (const auto& func : *functions) {
        integrals->push_back(func->integrateWRT(var));
    }
    for (size_t i = 0; i < transitions->size(); i++)
    {
        auto x = transitions->at(i)->getValue();
        auto oldvalue = var->getValue();
        var->setValue(x);
        auto fi = integrals->at(i)->getValue();
        auto fi1 = integrals->at(i + 1)->getValue();
        var->setValue(oldvalue);
        auto integConstant = fi - fi1;
        integrals->at(i + 1)->setIntegrationConstant(integConstant);
        noop();
    }
    answer->expression = std::make_shared<PiecewiseFunction>(var, integrals, transitions);
    return answer;
}

double PiecewiseFunction::getValue()
{
    auto xval = xx->getValue();
    for (size_t i = 0; i < transitions->size(); i++)
    {
        if (xval < transitions->at(i)->getValue()) {
            return functions->at(i)->getValue();
        }
    }
    return functions->back()->getValue();
}

void PiecewiseFunction::arguments(Symsptr args)
{
    auto arguments = args->getTerms();
    xx = arguments->at(0);
    functions = arguments->at(1)->getTerms();
    transitions = arguments->at(2)->getTerms();
}

Symsptr PiecewiseFunction::clonesptr()
{
    return std::make_shared<PiecewiseFunction>(*this);
}

std::ostream& PiecewiseFunction::printOn(std::ostream& s) const
{
    s << "PiecewiseFunction(" << *xx << ", " << std::endl;
    s << "functions{" << std::endl;
    s << *functions->at(0) << std::endl;
    for (size_t i = 1; i < functions->size(); i++)
    {
        s << *functions->at(i) << std::endl;
    }
    s << "}, " << std::endl;
    s << "transitions{" << std::endl;
    s << *transitions->at(0) << std::endl;
    for (size_t i = 1; i < transitions->size(); i++)
    {
        s << *transitions->at(i) << std::endl;
    }
    s << "})" << std::endl;
    return s;
}
