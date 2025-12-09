/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>

#include "DifferenceOperator.h"
#include "SingularMatrixError.h"
#include "FullRow.h"
#include "LDUFullMatParPvRobust.h"
#include "SimulationStoppingError.h"

using namespace MbD;

FRowDsptr DifferenceOperator::OneOverFactorials = []() {
    auto oneOverFactorials = FullRow<double>::With(10);
    for (size_t i = 0; i < oneOverFactorials->size(); i++)
    {
        oneOverFactorials->at(i) = 1.0 / std::tgamma(i + 1);
    }
    return oneOverFactorials;
}();

void DifferenceOperator::initialize()
{
    //Do nothing
}

void DifferenceOperator::calcOperatorMatrix()
{
    //Compute operatorMatrix such that 
    //value(time) : = (operatorMatrix at : 1) timesColumn : series.
    //valuedot(time) : = (operatorMatrix at : 2) timesColumn : series.
    //valueddot(time) : = (operatorMatrix at : 3) timesColumn : series.

    formTaylorMatrix();
    try {
        auto matrixSolver = std::make_shared<LDUFullMatParPvRobust>();
        operatorMatrix = matrixSolver->inversesaveOriginal(taylorMatrix, false);
        noop();    //For Debug
    }
    catch (SingularMatrixError ex) {
        throw SimulationStoppingError("To be implemented.");
    }
}

void DifferenceOperator::initializeLocally()
{
    throw SimulationStoppingError("To be implemented.");
}

void DifferenceOperator::setiStep(size_t i)
{
    iStep = i;
}

void DifferenceOperator::setorder(size_t o)
{
    order = o;
}

void DifferenceOperator::formTaylorMatrix()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void DifferenceOperator::instantiateTaylorMatrix()
{
    if (taylorMatrix == nullptr || (taylorMatrix->nrow() != (order + 1))) {
        taylorMatrix = FullMatrix<double>::With(order + 1, order + 1);
    }
}

void DifferenceOperator::formTaylorRowwithTimeNodederivative(size_t i, size_t ii, size_t k)
{
    //| rowi hi hipower aij |
    auto& rowi = taylorMatrix->at(i);
    for (size_t j = 0; j < k; j++)
    {
        rowi->at(j) = 0.0;
    }
    rowi->at(k) = 1.0;
    auto hi = timeNodes->at(ii) - time;
    auto hipower = 1.0;
    for (size_t j = k + 1; j < order + 1; j++)
    {
        hipower = hipower * hi;
        auto aij = hipower * OneOverFactorials->at(j - k);
        rowi->atiput(j, aij);
    }
}

void DifferenceOperator::settime(double t)
{
    time = t;
}

void DifferenceOperator::formDegenerateTaylorRow(size_t i) const
{
    auto& rowi = taylorMatrix->at(i);
    rowi->atiput(0, 1.0);
    for (size_t i = 1; i < order + 1; i++)
    {
        rowi->atiput(i, 0.0);
    }
}

double DifferenceOperator::currentStepSize() const
{
    return time - timeNodes->at(1);
}

size_t DifferenceOperator::direction() const
{
    return timeNodes->at(1) < time ? 1 : -1;
}

bool DifferenceOperator::isConstantStepFor(size_t nsteps) const
{
    auto nPastNodes = timeNodes->size();
    if (nPastNodes < nsteps) return false;
    auto dt = time - timeNodes->at(1);
    auto tol = std::abs(1.0e-6 * dt);
    for (size_t i = 1; i < nsteps; i++)
    {
        auto dti = timeNodes->at(i - 1)
            - timeNodes->at(i);
        if (std::abs(dti - dt) > tol) return false;
    }
    return true;
}

bool DifferenceOperator::isDecreasingStepFor(size_t nsteps) const
{
    auto nPastNodes = timeNodes->size();
    if (nPastNodes < nsteps) return false;
    auto oneMinusTolFactor = 1.0 - 1.0e-6;
    auto dtPast = time - timeNodes->at(1);
    dtPast = std::abs(dtPast);
    for (size_t i = 1; i < nsteps; i++)
    {
        auto dtNow = dtPast;
        dtPast = timeNodes->at(i - 1) - timeNodes->at(i);
        dtPast = std::abs(dtPast);

        if (dtNow > (oneMinusTolFactor * dtPast)) return false;
    }
    return true;
}

bool DifferenceOperator::isIncreasingStepFor(size_t nsteps) const
{
    auto nPastNodes = timeNodes->size();
    if (nPastNodes < (nsteps + 1)) return false;
    auto onePlusTolFactor = 1.0 + 1.0e-6;
    auto dtPast = time - timeNodes->at(1);
    dtPast = std::abs(dtPast);
    for (size_t i = 1; i < nsteps + 1; i++)
    {
        auto dtNow = dtPast;
        dtPast = timeNodes->at(i - 1) - timeNodes->at(i);
        dtPast = std::abs(dtPast);

        if (dtNow > (onePlusTolFactor * dtPast)) return false;
    }
    return true;
}

FColDsptr DifferenceOperator::valueWith(std::shared_ptr<std::vector<FColDsptr>> ypast)
{
    //"series stores past values for Extrapolator."
    //"series stores present and past values for BackwardDifference."

    return derivativewith(0, ypast);
}

FColDsptr DifferenceOperator::derivativewith(size_t deriv, std::shared_ptr<std::vector<FColDsptr>> series) const
{
    //"Answer ith derivative given past values in series."
    auto& coeffs = operatorMatrix->at(deriv);
    auto answer = coeffs->dot(series);
    return std::static_pointer_cast<FullColumn<double>>(answer);
}

FColDsptr DifferenceOperator::derivativeatpresentpast(size_t n, double t, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void DifferenceOperator::noop()
{
    //No Operations
}
