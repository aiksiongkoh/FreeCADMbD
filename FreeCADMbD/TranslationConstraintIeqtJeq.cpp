/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIeqtJeq.h"
#include "DispCompIeqctJeqcKeqct.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeqtJeq> TranslationConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIeqtJeq>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIeqtJeq::initriIeJeIe()
{
    riIeJeIe = DispCompIeqctJeqcKeqct::With(frmIe, frmJe, frmIe, axisI);
}

ConstraintType TranslationConstraintIeqtJeq::type()
{
    return essential;
}

void TranslationConstraintIeqtJeq::preVelIC()
{
    TranslationConstraintIeJe::preVelIC();
    pGpt = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe)->pvaluept();
}

void TranslationConstraintIeqtJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void TranslationConstraintIeqtJeq::preAccIC()
{
    TranslationConstraintIeJe::preAccIC();
    auto riIeJeIeqct = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe);
    ppGpXIpt = riIeJeIeqct->ppvaluepXIpt();
    ppGpEIpt = riIeJeIeqct->ppvaluepEIpt()->plusFullRow(riIeJeIeqct->ppvaluepEKpt());
    ppGpXJpt = riIeJeIeqct->ppvaluepXJpt();
    ppGpEJpt = riIeJeIeqct->ppvaluepEJpt();
    ppGptpt = riIeJeIeqct->ppvalueptpt();
}

void TranslationConstraintIeqtJeq::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIeqJeq::fillAccICIterError(col);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 2.0 * ppGpXIpt->timesFullColumn(qXdotI);
    sum += 2.0 * ppGpEIpt->timesFullColumn(qEdotI);
    sum += 2.0 * ppGpXJpt->timesFullColumn(qXdotJ);
    sum += 2.0 * ppGpEJpt->timesFullColumn(qEdotJ);
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}
