/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIeJeq.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "DispCompIecJeqcKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeJeq> TranslationConstraintIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIeJeq>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIeJeq::simUpdateAll()
{
    TranslationConstraintIeJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEJpEJ();
}

void TranslationConstraintIeJeq::initriIeJeIe()
{
    riIeJeIe = DispCompIecJeqcKec::With(frmIe, frmJe, frmIe, axisI);
}

void TranslationConstraintIeJeq::useEquationNumbers()
{
    TranslationConstraintIeJe::useEquationNumbers();
    iqXJ = frmJe->iqX();
    iqEJ = frmJe->iqE();
}

void TranslationConstraintIeJeq::fillpFpy(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIeJeq::fillpFpydot(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIeJeq::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //frmIec does not have q, we use frmJeq
    //aFJeO = lam * pGpXJ
    //aFIeO = -aFJeO
    auto aFJeO = pGpXJ->transpose()->times(lam);
    col->equalSelfMinus(aFJeO);
}

void TranslationConstraintIeJeq::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeq
    //aFJeO = lam * pGpXJ
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - p(aAOJp * rJpJeJp)pEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - (pAOJppEJ * rJpJeJp)T * aFJeO)
    //aTJeO = rIeJeO cross aFIeO - aTIeO
    //aTIeO = rJeIeO cross aFJeO - aTJeO

    auto aFJeOT = pGpXJ->times(lam);
    auto rJpJeJp = frmJe->rpep();
    auto pAOJppEJ = frmJe->pAOppE();
    auto aBOJp = frmJe->aBOp();
    auto prOJeOpEJTaFJeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOJeOpEJT * aFJeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOJeOpEJTaFJeOi = aFJeOT->timesFullColumn(pAOJppEJ->at(i)->timesFullColumn(rJpJeJp));
        prOJeOpEJTaFJeO->atiput(i, prOJeOpEJTaFJeOi);
    }
    auto lampGpEJ = pGpEJ->transpose()->times(lam);  //lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ->minusFullColumn(prOJeOpEJTaFJeO))->times(0.5);
    auto rJeIeO = getrIeJeO()->negated();
    auto aFJeO = aFJeOT->transpose();
    auto aTIeO = rJeIeO->cross(aFJeO)->minusFullColumn(aTJeO);
    col->equalSelfPlus(aTIeO);
}

void TranslationConstraintIeJeq::fillPosICError(FColDsptr col)
{
    TranslationConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIeJeq::fillPosICJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIeJeq::fillPosKineJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIeJeq::fillVelICJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::TranslationConstraintIeJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIeJeq::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void MbD::TranslationConstraintIeJeq::calcpGpXJ()
{
    pGpXJ = riIeJeIe->pvaluepXJ();
}

void MbD::TranslationConstraintIeJeq::calcpGpEJ()
{
    pGpEJ = riIeJeIe->pvaluepEJ();
}
