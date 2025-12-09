/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "LimitIJ.h"
#include "Constraint.h"
#include "SimulationStoppingError.h"

using namespace MbD;

bool LimitIJ::satisfied() const
{
    auto& constraint = constraints->front();
    if (type == "=<") {
        return constraint->aG < tol;
    }
    else if (type == "=>") {
        return constraint->aG > -tol;
    }
    throw SimulationStoppingError("To be implemented.");
    return true;
}

void LimitIJ::deactivate()
{
    active = false;
}

void LimitIJ::activate()
{
    active = true;
}

void LimitIJ::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    if (active) {
        ConstraintSet::fillConstraints(allConstraints);
    }
}

void LimitIJ::fillPosICError(FColDsptr col)
{
    if (active) {
        ConstraintSet::fillPosICError(col);
    }
}

void LimitIJ::fillPosICJacob(SpMatDsptr mat)
{
    if (active) {
        ConstraintSet::fillPosICJacob(mat);
    }
}

void LimitIJ::fillqsulam(FColDsptr col)
{
    if (active) {
        ConstraintSet::fillqsulam(col);
    }
}

void LimitIJ::setqsulam(FColDsptr col)
{
    if (active) {
        ConstraintSet::setqsulam(col);
    }
}

void LimitIJ::useEquationNumbers()
{
    if (active) {
        ConstraintSet::useEquationNumbers();
    }
}
