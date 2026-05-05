/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIetJeq.h"
#include "DirectionCosineIectJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIetJeq> DirectionCosineConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void MbD::DirectionCosineConstraintIetJeq::preAccIC()
{
    DirectionCosineConstraintIeJeq::preAccIC();
    ppGpEJpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->ppAijIeJepEJpt;
    ppGptpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->ppAijIeJeptpt;
}

void MbD::DirectionCosineConstraintIetJeq::preVelIC()
{
    DirectionCosineConstraintIeJeq::preVelIC();
    pGpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIetJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIectJeqc::With(eFrmI, eFrmJ, axisI, axisJ);
}

void MbD::DirectionCosineConstraintIetJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType MbD::DirectionCosineConstraintIetJeq::type()
{
    return essential;
}

void DirectionCosineConstraintIetJeq::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeJeq::fillAccICIterError(col);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += (ppGpEJpt->timesFullColumn(qEdotJ)) * 2.0;
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}

