/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>
#include <assert.h>
#include <unordered_set>

#include "Symbolic.h"
#include "System.h"
#include "Units.h"
#include "Constant.h"
#include "Variable.h"
#include "Product.h"
#include "Sum.h"
#include "Power.h"
#include "MbDSymbolicFunction.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<Symbolic> Symbolic::With()
{
    auto inst = std::make_shared<Symbolic>();
    inst->initialize();
    return inst;
}

void Symbolic::initialize()
{
    //Do nothing.
}

Symsptr Symbolic::times(Symsptr arg, Symsptr arg1)
{
    if (arg->isProduct()) {
        if (arg1->isProduct()) {
            auto newTerms = arg->getTerms();
            auto arg1Terms = arg1->getTerms();
            newTerms->insert(newTerms->end(), arg1Terms->begin(), arg1Terms->end());
            return std::make_shared<Product>(newTerms);
        }
        else {
            auto newTerms = arg->getTerms();
            newTerms->insert(newTerms->end(), arg1);
            return std::make_shared<Product>(newTerms);
        }
    }
    else {
        if (arg1->isProduct()) {
            auto newTerms = arg1->getTerms();
            newTerms->insert(newTerms->begin(), arg);
            return std::make_shared<Product>(newTerms);
        }
        else {
            return std::make_shared<Product>(arg, arg1);
        }
    }
}

Symsptr Symbolic::sum(Symsptr arg, Symsptr arg1)
{
    if (arg->isSum()) {
        if (arg1->isSum()) {
            auto newTerms = arg->getTerms();
            auto arg1Terms = arg1->getTerms();
            newTerms->insert(newTerms->end(), arg1Terms->begin(), arg1Terms->end());
            return std::make_shared<Sum>(newTerms);
        }
        else {
            auto newTerms = arg->getTerms();
            newTerms->insert(newTerms->end(), arg1);
            return std::make_shared<Sum>(newTerms);
        }
    }
    else {
        if (arg1->isSum()) {
            auto newTerms = arg1->getTerms();
            newTerms->insert(newTerms->begin(), arg);
            return std::make_shared<Sum>(newTerms);
        }
        else {
            return std::make_shared<Sum>(arg, arg1);
        }
    }
}

Symsptr Symbolic::differentiateWRT(Symsptr)
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

Symsptr Symbolic::integrateWRT(Symsptr)
{
    throw SimulationStoppingError("To be implemented.");
    return Symsptr();
}

Symsptr Symbolic::simplified()
{
    //std::cout << "sptr " << *sptr << std::endl;
    auto set = std::make_shared<std::unordered_set<Symsptr>>();
    auto expanded = expandUntil(set);
    //std::cout << "expanded " << *expanded << std::endl;
    auto set1 = std::make_shared<std::unordered_set<Symsptr>>();
    auto simplified = expanded->simplifyUntil(expanded, set1);
    //std::cout << "simplified " << *simplified << std::endl;
    return simplified;
}

Symsptr Symbolic::simplified(Symsptr sptr)
{
    //std::cout << "sptr " << *sptr << std::endl;
    auto set = std::make_shared<std::unordered_set<Symsptr>>();
    auto expanded = sptr->expandUntil(sptr, set);
    //std::cout << "expanded " << *expanded << std::endl;
    auto set1 = std::make_shared<std::unordered_set<Symsptr>>();
    auto simplified = expanded->simplifyUntil(expanded, set1);
    //std::cout << "simplified " << *simplified << std::endl;
    return simplified;
}

Symsptr Symbolic::expandUntil(std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    return expandUntil(clonesptr(), set);
}

Symsptr Symbolic::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
    throw SimulationStoppingError("To be implemented.");
    return sptr;
}

Symsptr Symbolic::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
    throw SimulationStoppingError("To be implemented.");
    return sptr;
}

bool Symbolic::isZero()
{
    return false;
}

bool Symbolic::isOne()
{
    return false;
}

bool Symbolic::isSum()
{
    return false;
}

bool Symbolic::isProduct()
{
    return false;
}

bool Symbolic::isConstant()
{
    return false;
}

std::ostream& Symbolic::printOn(std::ostream& s) const
{
    std::string str = typeid(*this).name();
    auto classname = str.substr(11, str.size() - 11);
    s << classname;
    return s;
}

std::shared_ptr<std::vector<Symsptr>> Symbolic::getTerms()
{
    throw SimulationStoppingError("To be implemented.");
    return std::make_shared<std::vector<Symsptr>>();
}

void Symbolic::addTerm(Symsptr trm)
{
    getTerms()->push_back(trm);
}

double Symbolic::getValue()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

void Symbolic::setValue(double)
{
    throw SimulationStoppingError("To be implemented.");
}

void Symbolic::createMbD()
{
    throw SimulationStoppingError("To be implemented.");
    return;
}

Symsptr Symbolic::clonesptr()
{
    //Return shallow copy of *this wrapped in shared_ptr
    throw SimulationStoppingError("To be implemented.");
    return std::make_shared<Symbolic>(*this);
}

std::shared_ptr<Constant> Symbolic::sptrConstant(double value)
{
    return Constant::With(value);
}

bool Symbolic::isVariable()
{
    return false;
}

void Symbolic::setIntegrationConstant(double integConstant)
{
    throw SimulationStoppingError("To be implemented.");
}

void Symbolic::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
    //Do nothing.
}

void Symbolic::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
    //Do nothing.
}

void Symbolic::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
    //Do nothing.
}

void Symbolic::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
    //Do nothing.
}

Symsptr Symbolic::raisedTo(Symsptr x, Symsptr y)
{
    return Power::With(x, y);
}

const std::string& Symbolic::getName() const {
    static const std::string empty = "";
    return empty;
}
