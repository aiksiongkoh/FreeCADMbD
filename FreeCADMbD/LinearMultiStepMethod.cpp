/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "LinearMultiStepMethod.h"
#include "FullColumn.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<LinearMultiStepMethod> LinearMultiStepMethod::With()
{
    auto inst = std::make_shared<LinearMultiStepMethod>();
    inst->initialize();
    return inst;
}

FColDsptr LinearMultiStepMethod::derivativeatpresentpast(size_t n, double t, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast)
{
    //"Interpolate or extrapolate."
    //"dfdt(t) = df0dt + d2f0dt2*(t - t0) + d3f0dt3*(t - t0)^2 / 2! + ..."

    auto answer = derivativepresentpast(n, y, ypast);
    if (t != time) {
        auto dt = t - time;
        auto dtpower = 1.0;
        for (size_t i = n + 1; i <= order; i++)
        {
            auto diydti = derivativepresentpast(i, y, ypast);
            dtpower = dtpower * dt;
            answer->equalSelfPlusFullColumntimes(diydti, dtpower * (OneOverFactorials->at(i - n)));
        }
    }
    return answer;
}

FColDsptr LinearMultiStepMethod::derivativepresentpast(size_t, FColDsptr, std::shared_ptr<std::vector<FColDsptr>>)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

double LinearMultiStepMethod::pvdotpv()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

double LinearMultiStepMethod::firstPastTimeNode()
{
    return timeNodes->at(0);
}

FColDsptr LinearMultiStepMethod::derivativepresentpastpresentDerivativepastDerivative(size_t,
    FColDsptr, std::shared_ptr<std::vector<FColDsptr>>,
    FColDsptr, std::shared_ptr<std::vector<FColDsptr>>)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}
