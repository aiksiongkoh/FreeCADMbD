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
    class Reciprocal : public FunctionX
    {
        //
    public:
        Reciprocal() = default;
        Reciprocal(Symsptr arg) : FunctionX(arg) {}
        static std::shared_ptr<Reciprocal> With();
        static std::shared_ptr<Reciprocal> With(Symsptr arg);

        double getValue() override;
        Symsptr differentiateWRTx() override;
        Symsptr integrateWRTx() override;
        Symsptr copyWith(Symsptr arg) override;

        std::ostream& printOn(std::ostream& s) const override;

    };
}

