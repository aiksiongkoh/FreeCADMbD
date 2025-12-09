/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "BackwardDifference.h"
#include "FullColumn.h"

using namespace MbD;

std::shared_ptr<BackwardDifference> BackwardDifference::With()
{
    auto inst = std::make_shared<BackwardDifference>();
    inst->initialize();
    return inst;
}

FColDsptr BackwardDifference::derivativepresentpast(size_t deriv, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast)
{
    //"Answer ith derivative given present value and past values."

    if (deriv == 0) { return y->copy(); }
    auto series = std::make_shared<FullRow<FColDsptr>>(deriv + 1);
    series->atiput(0, y);
    for (size_t i = 1; i < deriv + 1; i++)
    {
        series->atiput(i, (ypast->at(i - 1)));
    }

    auto& coeffs = operatorMatrix->at(deriv - 1);
    size_t n = coeffs->size();
    auto answer = series->at(0)->times(coeffs->at(0));
    for (size_t i = 1; i < n; i++) {
        answer->equalSelfPlusFullVectortimes(series->at(i), coeffs->at(i));
    }
    return answer;
}

void BackwardDifference::formTaylorMatrix()
{
    //"
    //For method order 3:
    //| 1        0                0                    0        |    |q(t) |        =    | q(t)    |
    //|    1    (t1 - t)    (t1 - t) ^ 2 / 2!    (t1 - t) ^ 3 / 3!|    |qd(t)    |        |q(t1)    |
    //|    1    (t2 - t)    (t2 - t) ^ 2 / 2!    (t2 - t) ^ 3 / 3!|    |qdd(t)    |        |q(t2)    |
    //|    1    (t3 - t)    (t3 - t) ^ 2 / 2!    (t3 - t) ^ 3 / 3!|    |qddd(t)|        |q(t3) |
    //"

    instantiateTaylorMatrix();
    formDegenerateTaylorRow(0);
    for (size_t i = 1; i < order + 1; i++)
    {
        formTaylorRowwithTimeNodederivative(i, i - 1, 0);
    }
}

double BackwardDifference::pvdotpv()
{
    return operatorMatrix->at(1)->at(0);
}

FColDsptr BackwardDifference::derivativepresentpastpresentDerivativepastDerivative(size_t n,
    FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast, FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast)
{
    return derivativepresentpast(n, y, ypast);
}

FColDsptr BackwardDifference::derivativewith(size_t deriv, std::shared_ptr<std::vector<FColDsptr>> series)
{
    //"Answer ith derivative given present value and past values in series."
    if (deriv == 0) {
        return series->at(0)->clonesptr();
    }
    return LinearMultiStepMethod::derivativewith(deriv, series);
}
