/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Function.h"
#include <unordered_set>

namespace MbD {
    class Symbolic;
    //using Symsptr = Symsptr;

    class FunctionX : public Function
    {
        //
    public:
        FunctionX() {}
        FunctionX(Symsptr arg) : xx(arg) {}
        static std::shared_ptr<FunctionX> With();
        
        void arguments(Symsptr args) override;
        virtual Symsptr copyWith(Symsptr arg);
        Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr differentiateWRT(Symsptr var) override;
        Symsptr integrateWRT(Symsptr var) override;
        virtual Symsptr differentiateWRTx();
        virtual Symsptr integrateWRTx();
        void createMbD() override;
        double getValue() override;
        bool isConstant() override;

        Symsptr xx;



    };
}

