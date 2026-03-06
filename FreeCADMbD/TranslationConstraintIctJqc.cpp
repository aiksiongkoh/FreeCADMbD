/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIctJqc.h"
#include "DispCompIectJeqcKect.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIctJqc> TranslationConstraintIctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIctJqc>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIctJqc::initriIeJeIe()
{
    riIeJeIe = DispCompIectJeqcKect::With(eFrmI, eFrmJ, eFrmI, axisI);
}

ConstraintType TranslationConstraintIctJqc::type()
{
    return essential;
}

void TranslationConstraintIctJqc::preVelIC()
{
    TranslationConstraintIJ::preVelIC();
    pGpt = std::static_pointer_cast<DispCompIectJeqcKect>(riIeJeIe)->pvaluept();
}

void TranslationConstraintIctJqc::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void TranslationConstraintIctJqc::preAccIC()
{
    TranslationConstraintIJ::preAccIC();
    auto riIeJeIeqct = std::static_pointer_cast<DispCompIectJeqcKect>(riIeJeIe);
    ppGpXJpt = riIeJeIeqct->ppvaluepXJpt();
    ppGpEJpt = riIeJeIeqct->ppvaluepEJpt();
    ppGptpt = riIeJeIeqct->ppvalueptpt();
}

void TranslationConstraintIctJqc::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIcJqc::fillAccICIterError(col);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotJ = eFrmJqc->qXdot();
    auto qEdotJ = eFrmJqc->qEdot();
    auto sum = 2.0 * ppGpXJpt->timesFullColumn(qXdotJ);
    sum += 2.0 * ppGpEJpt->timesFullColumn(qEdotJ);
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}
