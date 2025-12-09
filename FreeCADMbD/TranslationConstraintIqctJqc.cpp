/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqctJqc.h"
#include "DispCompIeqctJeqcKeqct.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIqctJqc> TranslationConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIqctJqc>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIqctJqc::initriIeJeIe()
{
    riIeJeIe = DispCompIeqctJeqcKeqct::With(eFrmI, eFrmJ, eFrmI, axisI);
}

ConstraintType TranslationConstraintIqctJqc::type()
{
    return essential;
}

void TranslationConstraintIqctJqc::preVelIC()
{
    TranslationConstraintIJ::preVelIC();
    pGpt = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe)->pvaluept();
}

void TranslationConstraintIqctJqc::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void TranslationConstraintIqctJqc::preAccIC()
{
    TranslationConstraintIJ::preAccIC();
    auto riIeJeIeqct = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe);
    ppGpXIpt = riIeJeIeqct->ppvaluepXIpt();
    ppGpEIpt = riIeJeIeqct->ppvaluepEIpt()->plusFullRow(riIeJeIeqct->ppvaluepEKpt());
    ppGpXJpt = riIeJeIeqct->ppvaluepXJpt();
    ppGpEJpt = riIeJeIeqct->ppvaluepEJpt();
    ppGptpt = riIeJeIeqct->ppvalueptpt();
}

void TranslationConstraintIqctJqc::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIqcJqc::fillAccICIterError(col);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto qXdotJ = eFrmJqc->qXdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = 2.0 * ppGpXIpt->timesFullColumn(qXdotI);
    sum += 2.0 * ppGpEIpt->timesFullColumn(qEdotI);
    sum += 2.0 * ppGpXJpt->timesFullColumn(qXdotJ);
    sum += 2.0 * ppGpEJpt->timesFullColumn(qEdotJ);
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}
