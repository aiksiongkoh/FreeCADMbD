/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "BackwardDifference.h"

namespace MbD {


#pragma once
    class StartingBDF : public BackwardDifference
    {
        //
    public:
        static std::shared_ptr<StartingBDF> With();
        void initialize() override;

        void initializeLocally() override;
        void formTaylorMatrix() override;
        void setorder(size_t o) override;
        FColDsptr derivativepresentpastpresentDerivativepastDerivative(size_t n,
            FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast,
            FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast);


    };
}
