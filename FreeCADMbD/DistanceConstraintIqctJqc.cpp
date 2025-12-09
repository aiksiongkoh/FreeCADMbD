/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIqctJqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIqctJqc> DistanceConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistanceConstraintIqctJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistanceConstraintIqctJqc::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType DistanceConstraintIqctJqc::type()
{
    return essential;
}
