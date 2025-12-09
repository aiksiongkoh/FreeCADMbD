/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "LinearMultiStepMethod.h"

namespace MbD {
    class BackwardDifference : public LinearMultiStepMethod
    {
        //
    public:
        static std::shared_ptr<BackwardDifference> With();
        
        FColDsptr derivativepresentpast(size_t order, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast) override;
        void formTaylorMatrix() override;
        double pvdotpv() override;
        FColDsptr derivativepresentpastpresentDerivativepastDerivative(size_t n,
            FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast,
            FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast);
        FColDsptr derivativewith(size_t deriv, std::shared_ptr<std::vector<FColDsptr>> series);


    };
}
