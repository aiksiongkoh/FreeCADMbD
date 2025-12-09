/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "StartingBDF.h"
#include "FullColumn.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<StartingBDF> StartingBDF::With()
{
    auto inst = std::make_shared<StartingBDF>();
    inst->initialize();
    return inst;
}

void StartingBDF::initialize()
{
    BackwardDifference::initialize();
    iStep = 0;
    order = iStep + 1;
}

void StartingBDF::initializeLocally()
{
    iStep = 0;
    order = iStep + 1;
}

void StartingBDF::formTaylorMatrix()
{
    //"
    //For method order 3: 
    //|    1        0        0                0        |    |q(t)    |    =    |q(t)    | 
    //|    1    (t1 - t)    (t1 - t)^2/2!        (t1 - t)^3/3!    |    |qd(t)    |        |q(t1)    | 
    //|    1    (t2 - t)    (t2 - t)^2/2!        (t2 - t)^3/3!    |    |qdd(t)    |        |q(t2)    | 
    //|    0        1        (t2 - t)        (t2 - t)^2/2!    |    |qddd(t)|        |qd(t2)    | 
    //"

    instantiateTaylorMatrix();
    formDegenerateTaylorRow(0);
    for (size_t i = 1; i < order; i++)
    {
        formTaylorRowwithTimeNodederivative(i, i - 1, 0);
    }
    formTaylorRowwithTimeNodederivative(order + 1, order - 1, 1);
}

void StartingBDF::setorder(size_t o)
{
    //"order is controlled by iStep."
    if (order != o) throw std::runtime_error("iStep and order must be consistent.");
}

FColDsptr StartingBDF::derivativepresentpastpresentDerivativepastDerivative(size_t n, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast, FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}
