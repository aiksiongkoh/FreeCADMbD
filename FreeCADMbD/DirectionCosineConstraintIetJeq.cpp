/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIetJeq.h"
#include "DirectionCosineIetJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIetJeq> DirectionCosineConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIetJeq::preAccIC()
{
    DirectionCosineConstraintIeJeq::preAccIC();
    ppGpEJpt = std::static_pointer_cast<DirectionCosineIetJeq>(aAijIeJe)->ppAijIeJepEJpt;
    ppGptpt = std::static_pointer_cast<DirectionCosineIetJeq>(aAijIeJe)->ppAijIeJeptpt;
}

void DirectionCosineConstraintIetJeq::preVelIC()
{
    DirectionCosineConstraintIeJeq::preVelIC();
    pGpt = std::static_pointer_cast<DirectionCosineIetJeq>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIetJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIetJeq::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIetJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType DirectionCosineConstraintIetJeq::type()
{
    return essential;
}

void DirectionCosineConstraintIetJeq::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeJeq::fillAccICIterError(col);
    auto eFrmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotJ = eFrmJeq->qEdot();
    double sum = 0.0;
    sum += (ppGpEJpt->timesFullColumn(qEdotJ)) * 2.0;
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}

