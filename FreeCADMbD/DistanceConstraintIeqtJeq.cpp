/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIeqtJeq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIeqtJeq> DistanceConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistanceConstraintIeqtJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistanceConstraintIeqtJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType DistanceConstraintIeqtJeq::type()
{
    return essential;
}
