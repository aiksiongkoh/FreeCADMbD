/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIeqJe.h"
#include "DispCompIeqcJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeqJe> TranslationConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIeqJe>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIeqJe::initriIeJeIe()
{
    riIeJeIe = DispCompIeqcJecKeqc::With(frmIe, frmJe, frmIe, axisI);
}

void MbD::TranslationConstraintIeqJe::calcpGpXI()
{
    pGpXI = riIeJeIe->pvaluepXI();
}

void MbD::TranslationConstraintIeqJe::calcpGpEI()
{
    //frmIe = frmKe
    pGpEI = (riIeJeIe->pvaluepEI())->plusFullRow(riIeJeIe->pvaluepEK());
}

void MbD::TranslationConstraintIeqJe::calcppGpXIpEI()
{
    ppGpXIpEI = riIeJeIe->ppvaluepXIpEK();
}

void MbD::TranslationConstraintIeqJe::calcppGpEIpEI()
{
    //frmIe = frmKe
    //rIeJeKe = aAOKeT * (rOJeO - rOIeO)
    //prIeJeKepEI = aAOKeT * (- prOIeOpEI)
    //prIeJeKepEK = pAOKeTpEK * (rOJeO - rOIeO)
    //pprIeJeKepEIpEI = aAOKeT * (- pprOIeOpEIpEI)
    //pprIeJeKepEIpEK = pAOKeTpEK * (- prOIeOpEI)
    //pprIeJeKepEKpEK = ppAOKeTpEKpEK * (rOJeO - rOIeO)
    ppGpEIpEI = riIeJeIe->ppvaluepEIpEI()
        ->plusFullMatrix(riIeJeIe->ppvaluepEIpEK())
        ->plusFullMatrix((riIeJeIe->ppvaluepEIpEK()->transpose()
        ->plusFullMatrix(riIeJeIe->ppvaluepEKpEK())));
}

void TranslationConstraintIeqJe::useEquationNumbers()
{
    TranslationConstraintIeJe::useEquationNumbers();
    iqXI = frmIe->iqX();
    iqEI = frmIe->iqE();
}

void TranslationConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void TranslationConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void TranslationConstraintIeqJe::fillPosICError(FColDsptr col)
{
    TranslationConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void TranslationConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    assert(!ppGpXIpXI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void TranslationConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void TranslationConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void TranslationConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto sum = pGpXI->timesFullColumn(frmIeq->qXddot());
    sum += pGpEI->timesFullColumn(frmIeq->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}
