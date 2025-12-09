/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <sstream>
#include <string>

#include "Sum.h"
#include "Constant.h"
#include "Integral.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<Sum> Sum::With()
{
    auto inst = std::make_shared<Sum>();
    inst->initialize();
    return inst;
}

Symsptr Sum::parseExpression(std::string& expression)
{
    std::istringstream iss(expression);
    auto sum = std::make_shared<Sum>();
    sum->parse(iss);
    return sum->simplified(sum);
}

void Sum::parse(std::istringstream& iss)
{
    iss >> std::ws;
    char c = iss.peek();
    if (c == '+') {
        parsePlusTerm(iss);
    }
    else     if (c == '-') {
        parseMinusTerm(iss);
    }
    else {
        parseTerm(iss);
    }
}

void Sum::parseTerm(std::istringstream&)
{
    throw SimulationStoppingError("To be implemented.");
}

void Sum::parsePlusTerm(std::istringstream& iss)
{
    iss.get();
}

void Sum::parseMinusTerm(std::istringstream&)
{
    throw SimulationStoppingError("To be implemented.");
}

Symsptr Sum::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto itr = std::find_if(set->begin(), set->end(), [sptr](Symsptr sym) {return sptr.get() == sym.get(); });
    if (itr != set->end()) {
        auto answer = std::make_shared<Sum>();
        answer->terms = terms;
        return answer;
    }
    auto newTerms = std::make_shared<std::vector<Symsptr>>();
    for (const auto& term : *terms) {
        auto newTerm = term->expandUntil(term, set);
        if (newTerm->isSum()) {
            newTerms->insert(newTerms->end(), newTerm->getTerms()->begin(), newTerm->getTerms()->end());
        }
        else {
            newTerms->push_back(newTerm);
        }
    }
    auto newSize = newTerms->size();
    if (newSize == 0) {
        return sptrConstant(0.0);
    }
    else if (newSize == 1) {
        return newTerms->at(0);
    }
    else {
        auto answer = std::make_shared<Sum>();
        answer->terms = newTerms;
        return answer;
    }
}

Symsptr Sum::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto itr = std::find_if(set->begin(), set->end(), [this](Symsptr sym) {return this == (sym.get()); });
    if (itr != set->end()) {
        auto answer = std::make_shared<Sum>();
        answer->terms = terms;
        return answer;
    }
    auto newTerms = std::make_shared<std::vector<Symsptr>>();
    double constant = 0.0;
    for (const auto& term : *terms) {
        auto newTerm = term->simplifyUntil(term, set);
        if (newTerm->isConstant()) {
            constant += term->getValue();
        }
        else {
            newTerms->push_back(newTerm);
        }
    }
    if (newTerms->size() == 0 && constant == 0.0) {
        return sptrConstant(0.0);
    }
    if (constant != 0.0) {
        newTerms->insert(newTerms->begin(), sptrConstant(constant));
    }
    if (newTerms->size() == 1) {
        return newTerms->at(0);
    }
    auto answer = std::make_shared<Sum>();
    answer->terms = newTerms;
    return answer;
}

bool Sum::isSum()
{
    return true;
}

double Sum::getValue()
{
    double answer = 0.0;
    for (size_t i = 0; i < terms->size(); i++) answer += terms->at(i)->getValue();
    return answer;
}

Symsptr Sum::clonesptr()
{
    return std::make_shared<Sum>(*this);
}

Symsptr Sum::differentiateWRT(Symsptr var)
{
    auto derivatives = std::make_shared<std::vector<Symsptr>>();
    for (const auto& term : *terms) {
        auto deriv = term->differentiateWRT(var);
        derivatives->push_back(deriv);
    }
    auto answer = std::make_shared<Sum>();
    answer->terms = derivatives;
    return answer->simplified();
}

Symsptr Sum::integrateWRT(Symsptr var)
{
    auto simple = simplified();
    auto answer = std::make_shared<Integral>();
    answer->xx = var;
    answer->integrand = simple;;
    if (simple->isSum()) {
        auto newTerms = simple->getTerms();
        auto integrals = std::make_shared<std::vector<Symsptr>>(newTerms->size());
        std::transform(newTerms->begin(),
            newTerms->end(),
            integrals->begin(),
            [var](Symsptr term) { return term->integrateWRT(var); }
        );
        auto sum = std::make_shared<Sum>();
        sum->terms = integrals;
        answer->expression = sum->simplified();
    }
    else {
        answer->expression = simple->integrateWRT(var);
    }
    return answer;
}

std::ostream& Sum::printOn(std::ostream& s) const
{
    s << "(";
    s << *(terms->at(0));
    for (size_t i = 1; i < terms->size(); i++)
    {
        s << " + " << *(terms->at(i));
    }
    s << ")";
    return s;
}
