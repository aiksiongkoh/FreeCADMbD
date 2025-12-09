/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ExpressionX.h"
#include "Constant.h"

namespace MbD {
    class Integral : public ExpressionX
    {
    public:
        Integral() = default;
        Integral(Symsptr var, Symsptr integrand);
        static std::shared_ptr<Integral> With();
        
        void arguments(Symsptr args) override;
        Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        void setIntegrationConstant(double integConstant) override;
        double getValue() override;
        Symsptr clonesptr() override;

        std::ostream& printOn(std::ostream& s) const override;

        Symsptr integrand;
        Symsptr integrationConstant = sptrConstant(0.0);
    };
}
