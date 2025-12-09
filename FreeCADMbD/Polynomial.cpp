/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/


#include "Polynomial.h"
#include "Constant.h"
#include "Sum.h"
#include "Integral.h"

using namespace MbD;

Polynomial::Polynomial(Symsptr var, std::shared_ptr<std::vector<double>> coefficients)
{
    assert(!coefficients->empty());
    xx = var;
    std::transform(coefficients->begin(), coefficients->end(), coeffs->begin(),
        [&](auto& coeff) { return sptrConstant(coeff); }
    );
}
Polynomial::Polynomial(Symsptr var, std::shared_ptr<std::vector<Symsptr>> coefficients)
{
    assert(!coefficients->empty());
    xx = var;
    coeffs->insert(coeffs->end(), coefficients->begin(), coefficients->end());
}

std::shared_ptr<Polynomial> Polynomial::With()
{
    auto inst = std::make_shared<Polynomial>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Polynomial> Polynomial::With(Symsptr var, std::shared_ptr<std::vector<double>> coeffs)
{
    auto inst = std::make_shared<Polynomial>(var, coeffs);
    inst->initialize();
    return inst;
}

std::shared_ptr<Polynomial> Polynomial::With(Symsptr var, std::shared_ptr<std::vector<Symsptr>> coeffs)
{
    auto inst = std::make_shared<Polynomial>(var, coeffs);
    inst->initialize();
    return inst;
}

Symsptr Polynomial::expandUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto newCoeffs = std::make_shared<std::vector<Symsptr>>();
    for (size_t i = 0; i < coeffs->size(); i++)
    {
        auto coeff = coeffs->at(i);
        auto newCoeff = coeff->expandUntil(coeff, set);
        newCoeffs->push_back(newCoeff);
    }
    return Polynomial::With(xx, newCoeffs);
}

Symsptr Polynomial::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    auto newCoeffs = std::make_shared<std::vector<Symsptr>>();
    for (size_t i = 0; i < coeffs->size(); i++)
    {
        auto coeff = coeffs->at(i);
        auto newCoeff = coeff->simplifyUntil(coeff, set);
        newCoeffs->push_back(newCoeff);
    }
    return Polynomial::With(xx, newCoeffs);
}

Symsptr Polynomial::differentiateWRTx()
{
    //Differentiate powers
    if (coeffs->size() == 1) return sptrConstant(0.0);
    auto newCoeffs = std::make_shared<std::vector<Symsptr>>();
    for (size_t i = 1; i < coeffs->size(); i++)
    {
        auto newCoeff = i * coeffs->at(i)->getValue();
        newCoeffs->push_back(sptrConstant(newCoeff));
    }
    auto poly1 = std::make_shared<Polynomial>(xx, newCoeffs);
    //Differentiate coeffs
    auto coeffDerivs = std::make_shared<std::vector<Symsptr>>(coeffs->size());
    std::transform(coeffs->begin(),
        coeffs->end(),
        coeffDerivs->begin(),
        [&](auto& coeff) { return coeff->differentiateWRT(xx); }
    );
    auto poly2 = std::make_shared<Polynomial>(xx, coeffDerivs);
    return std::make_shared<Sum>(poly1, poly2);
}

Symsptr Polynomial::integrateWRT(Symsptr var)
{
    assert(xx == var);
    auto simple = simplified();
    auto answer = std::make_shared<Integral>();
    answer->xx = var;
    answer->integrand = simple;
    auto newCoeffs = std::make_shared<std::vector<Symsptr>>();
    newCoeffs->push_back(sptrConstant(0.0));
    for (size_t i = 0; i < coeffs->size(); i++)
    {
        auto newCoeff = coeffs->at(i)->getValue() / (i + 1);
        newCoeffs->push_back(sptrConstant(newCoeff));
    }
    answer->expression = std::make_shared<Polynomial>(var, newCoeffs);
    return answer;
}

double Polynomial::getValue()
{
    auto xvalue = xx->getValue();
    auto xpower = 1.0;
    auto answer = 0.0;
    for (size_t i = 0; i < coeffs->size(); i++)
    {
        answer += coeffs->at(i)->getValue() * xpower;
        xpower *= xvalue;
    }
    return answer;
}

Symsptr Polynomial::clonesptr()
{
    return std::make_shared<Polynomial>(*this);
}

std::ostream& Polynomial::printOn(std::ostream& s) const
{
    s << "Polynomial(";
    s << *xx << ", ";
    s << "coeffs{";
    s << *coeffs->at(0);
    for (size_t i = 1; i < coeffs->size(); i++)
    {
        s << ", " << *coeffs->at(i);
    }
    s << "})";
    return s;
}
