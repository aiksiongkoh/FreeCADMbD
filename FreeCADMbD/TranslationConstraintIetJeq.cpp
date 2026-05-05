/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIetJeq.h"
#include "DispCompIectJeqcKect.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIetJeq> TranslationConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIetJeq>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

ConstraintType TranslationConstraintIetJeq::type()
{
    return essential;
}

void TranslationConstraintIetJeq::preVelIC()
{
    TranslationConstraintIeJe::preVelIC();
    pGpt = riIeJeIe->pvaluept();
}

void TranslationConstraintIetJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void TranslationConstraintIetJeq::preAccIC()
{
    TranslationConstraintIeJe::preAccIC();
    ppGpXJpt = riIeJeIe->ppvaluepXJpt();
    ppGpEJpt = riIeJeIe->ppvaluepEJpt();
    ppGptpt = riIeJeIe->ppvalueptpt();
}

void TranslationConstraintIetJeq::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIeJeq::fillAccICIterError(col);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    auto sum = 2.0 * ppGpXJpt->timesFullColumn(qXdotJ);
    sum += 2.0 * ppGpEJpt->timesFullColumn(qEdotJ);
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}
