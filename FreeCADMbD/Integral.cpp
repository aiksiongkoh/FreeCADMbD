#include "Integral.h"
#include <cassert>
#include "SimulationStoppingError.h"

using namespace MbD;

Integral::Integral(Symsptr, Symsptr)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Integral> Integral::With()
{
    auto inst = std::make_shared<Integral>();
    inst->initialize();
    return inst;
}

void Integral::arguments(Symsptr args)
{
    auto arguments = args->getTerms();
    xx = arguments->at(0);
    integrand = arguments->at(1);
    expression = integrand->integrateWRT(xx);
}

Symsptr Integral::expandUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto expand = expression->expandUntil(expression, set);
    auto answer = std::make_shared<Integral>();
    answer->xx = xx;
    answer->expression = expand;
    answer->integrand = integrand;
    answer->integrationConstant = integrationConstant;
    return answer;
}

Symsptr Integral::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto simple = expression->simplifyUntil(expression, set);
    auto answer = std::make_shared<Integral>();
    answer->xx = xx;
    answer->expression = simple;
    answer->integrand = integrand;
    answer->integrationConstant = integrationConstant;
    return answer;
}

void Integral::setIntegrationConstant(double integConstant)
{
    integrationConstant = sptrConstant(integConstant);
}

double Integral::getValue()
{
    return expression->getValue() + integrationConstant->getValue();
}

Symsptr Integral::clonesptr()
{
    return std::make_shared<Integral>(*this);
}

std::ostream& Integral::printOn(std::ostream& s) const
{
    s << *expression << " + ";
    s << *integrationConstant;
    return s;
}
