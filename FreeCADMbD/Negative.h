/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "FunctionX.h"

namespace MbD {
    class Negative : public FunctionX
    {
        //
    public:
        Negative() = default;
        Negative(Symsptr arg) : FunctionX(arg) {}
        static std::shared_ptr<Negative> With(Symsptr sym);
        double getValue() override;
        Symsptr differentiateWRTx() override;
        Symsptr integrateWRTx() override;
        Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr copyWith(Symsptr arg) override;
        Symsptr clonesptr() override;

        std::ostream& printOn(std::ostream& s) const override;

    };
}

