/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqcJqc.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIqcJqc> TranslationConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIqcJqc>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIqcJqc::initriIeJeIe()
{
    riIeJeIe = DispCompIeqcJeqcKeqc::With(eFrmI, eFrmJ, eFrmI, axisI);
}

void TranslationConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    TranslationConstraintIqcJc::calcPostDynCorrectorIteration();
    pGpXJ = riIeJeIe->pvaluepXJ();
    pGpEJ = riIeJeIe->pvaluepEJ();
    ppGpEIpXJ = riIeJeIe->ppvaluepXJpEK()->transpose();
    ppGpEIpEJ = riIeJeIe->ppvaluepEJpEK()->transpose();
    ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIqcJqc::useEquationNumbers()
{
    TranslationConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJ = frmJeqc->iqX();
    iqEJ = frmJeqc->iqE();
}

void TranslationConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    TranslationConstraintIqcJc::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    TranslationConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    TranslationConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    TranslationConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    TranslationConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    TranslationConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = eFrmIqc->qEdot();
    auto qXdotJ = eFrmJqc->qXdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpXJ->timesFullColumn(eFrmJqc->qXddot());
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
