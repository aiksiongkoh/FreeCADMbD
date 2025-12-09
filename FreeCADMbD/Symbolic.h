/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <iostream>
#include <unordered_set>
#include <memory>
#include <ostream>

#include "MbDMath.h"

namespace MbD {
    class System;
    class Units;
    class Constant;
    class Variable;
    class Symbolic;
    class MbDSymbolicFunction;
    using Symsptr = std::shared_ptr<Symbolic>;
    using vecSymsptr = std::shared_ptr<std::vector<Symsptr>>;

    class Symbolic : public MbDMath
    {
    public:
        Symbolic() {}
        //virtual ~Symbolic() {}
        static std::shared_ptr<Symbolic> With();

        static Symsptr times(Symsptr arg, Symsptr arg1);
        static Symsptr sum(Symsptr arg, Symsptr arg1);
        static Symsptr raisedTo(Symsptr x, Symsptr y);
        virtual void initialize();

        virtual Symsptr differentiateWRT(Symsptr var);
        virtual Symsptr integrateWRT(Symsptr var);
        virtual Symsptr simplified();
        virtual Symsptr simplified(Symsptr sptr);
        virtual Symsptr expandUntil(std::shared_ptr<std::unordered_set<Symsptr>> set);
        virtual Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set);
        virtual Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set);
        virtual bool isZero();
        virtual bool isOne();
        virtual bool isSum();
        virtual bool isProduct();
        virtual bool isConstant();
        virtual std::shared_ptr<std::vector<Symsptr>> getTerms();
        virtual void addTerm(Symsptr trm);
        virtual double getValue();
        virtual void setValue(double val);
        virtual void createMbD();
        virtual Symsptr clonesptr();
        std::shared_ptr<Constant> sptrConstant(double value);
        virtual bool isVariable();
        virtual void setIntegrationConstant(double integConstant);
        virtual const std::string& getName() const;
        virtual void fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs);
        virtual void fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs);
        virtual void fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions);
        virtual void fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions);

        virtual std::ostream& printOn(std::ostream& s) const;
        friend std::ostream& operator<<(std::ostream& s, const Symbolic& sym)
        {
            return sym.printOn(s);
        }
    };
}

