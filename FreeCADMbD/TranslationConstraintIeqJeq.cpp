/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIeqJeq.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeqJeq> TranslationConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIeqJeq>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIeqJeq::simUpdateAll()
{
    TranslationConstraintIeqJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpEJpEJ();
}

void MbD::TranslationConstraintIeqJeq::calcpGpXJ()
{
    pGpXJ = riIeJeIe->pvaluepXJ();
}

void MbD::TranslationConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = riIeJeIe->pvaluepEJ();
}

void MbD::TranslationConstraintIeqJeq::calcppGpEIpXJ()
{
    ppGpEIpXJ = riIeJeIe->ppvaluepXJpEK()->transpose();
}

void MbD::TranslationConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = riIeJeIe->ppvaluepEJpEK()->transpose();
}

void MbD::TranslationConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIeqJeq::useEquationNumbers()
{
    TranslationConstraintIeqJe::useEquationNumbers();
    iqXJ = eFrmJ->iqX();
    iqEJ = eFrmJ->iqE();
}

void TranslationConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    TranslationConstraintIeqJe::fillpFpy(mat);
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

void TranslationConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    TranslationConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    TranslationConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    //aG = aAIeOT * (rOJeO - rOIeO)
    TranslationConstraintIeqJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);

    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);

    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);

    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    TranslationConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    TranslationConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
