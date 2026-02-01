/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIcJqc.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "DispCompIecJeqcKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIcJqc> TranslationConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIcJqc>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIcJqc::initriIeJeIe()
{
    riIeJeIe = DispCompIecJeqcKec::With(eFrmI, eFrmJ, eFrmI, axisI);
}

void TranslationConstraintIcJqc::calcPostDynCorrectorIteration()
{
    TranslationConstraintIJ::calcPostDynCorrectorIteration();
    pGpXJ = riIeJeIe->pvaluepXJ();
    pGpEJ = riIeJeIe->pvaluepEJ();
    ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIcJqc::useEquationNumbers()
{
    TranslationConstraintIJ::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJ = frmJeqc->iqX();
    iqEJ = frmJeqc->iqE();
}

void TranslationConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
    TranslationConstraintIJ::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
    TranslationConstraintIJ::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIcJqc::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ
    //aFIeO = -aFJeO
    auto aFJeO = pGpXJ->transpose()->times(lam);
    col->equalSelfMinus(aFJeO);
}

void TranslationConstraintIcJqc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - p(aAOJp * rJpJeJp)pEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - (pAOJppEJ * rJpJeJp)T * aFJeO)
    //aTJeO = rIeJeO cross aFIeO - aTIeO
    //aTIeO = rJeIeO cross aFJeO - aTJeO

    auto aFJeOT = pGpXJ->times(lam);
    auto rJpJeJp = eFrmJ->rpep();
    auto pAOJppEJ = eFrmJ->pAOppE();
    auto aBOJp = eFrmJ->aBOp();
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

void TranslationConstraintIcJqc::fillPosICError(FColDsptr col)
{
    TranslationConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
    TranslationConstraintIJ::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    TranslationConstraintIJ::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
    TranslationConstraintIJ::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIJ::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotJ = eFrmJqc->qXdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpXJ->timesFullColumn(eFrmJqc->qXddot());
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
