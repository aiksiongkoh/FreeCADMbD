/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineIeqtJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqtJeq> DirectionCosineConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqtJeq::preAccIC()
{
    DirectionCosineConstraintIeqJeq::preAccIC();
    ppGpEIpt = std::static_pointer_cast<DirectionCosineIeqtJeq>(aAijIeJe)->ppAijIeJepEIpt;
    ppGpEJpt = std::static_pointer_cast<DirectionCosineIeqtJeq>(aAijIeJe)->ppAijIeJepEJpt;
    ppGptpt = std::static_pointer_cast<DirectionCosineIeqtJeq>(aAijIeJe)->ppAijIeJeptpt;
}

void DirectionCosineConstraintIeqtJeq::preVelIC()
{
    DirectionCosineConstraintIeqJeq::preVelIC();
    pGpt = std::static_pointer_cast<DirectionCosineIeqtJeq>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIeqtJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqtJeq::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIeqtJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType DirectionCosineConstraintIeqtJeq::type()
{
    return essential;
}

void DirectionCosineConstraintIeqtJeq::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeqJeq::fillAccICIterError(col);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = frmIeq->qEdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = (ppGpEIpt->timesFullColumn(qEdotI)) * 2.0;
    sum += (ppGpEJpt->timesFullColumn(qEdotJ)) * 2.0;
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}

