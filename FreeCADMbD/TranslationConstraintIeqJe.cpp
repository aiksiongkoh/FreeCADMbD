/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIeqJe.h"
#include "DispCompIeqcJecKeqc.h"
#include "DispCompiIeJeKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeqJe> TranslationConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    auto inst = std::make_shared<TranslationConstraintIeqJe>(frmi, frmj, axisi);
    inst->initialize();
    return inst;
}

void TranslationConstraintIeqJe::simUpdateAll()
{
    TranslationConstraintIeJe::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpEI();
    calcppGpEIpEI();
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
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //prIeJeKepXI = aAOKeT * prIeJeOpXI
    //prIeJeKepEI = aAOKeT * prIeJeOpEI
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    //prIeJeKepEK = pAOKeTpEK * rIeJeO
    //pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    //pprIeJeKepEIpEI = aAOKeT * pprIeJeOpEIpEI
    //pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    //pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    //pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    //pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    ppGpEIpEI = riIeJeIe->ppvaluepEIpEI()
        ->plusFullMatrix(riIeJeIe->ppvaluepEIpEK())
        ->plusFullMatrix((riIeJeIe->ppvaluepEIpEK()->transpose()
        ->plusFullMatrix(riIeJeIe->ppvaluepEKpEK())));
}

void TranslationConstraintIeqJe::useEquationNumbers()
{
    TranslationConstraintIeJe::useEquationNumbers();
    iqXI = eFrmI->iqX();
    iqEI = eFrmI->iqE();
}

void TranslationConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void TranslationConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillpFpydot(mat);
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
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void TranslationConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void TranslationConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    TranslationConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void TranslationConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    TranslationConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto sum = pGpXI->timesFullColumn(frmIeq->qXddot());
    sum += pGpEI->timesFullColumn(frmIeq->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void TranslationConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //auto aFIeO = pGpXI->transpose()->times(lam);
    //col->equalSelfPlus(aFIeO);
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void TranslationConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    auto aFIeOT = pGpXI->times(lam);
    auto rIpIeIp = eFrmI->rpep();
    auto pAOIppEI = eFrmI->pAOppE();
    auto aBOIp = eFrmI->aBOp();
    auto prOIeOpEITaFIeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOIeOpEIT * aFIeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOIeOpEIi = pAOIppEI->at(i)->timesFullColumn(rIpIeIp);
        auto prOIeOpEITaFIeOi = aFIeOT->timesFullColumn(prOIeOpEIi);
        prOIeOpEITaFIeO->atiput(i, prOIeOpEITaFIeOi);
    }
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI->minusFullColumn(prOIeOpEITaFIeO))->times(0.5);
    col->equalSelfPlus(aTIeO);
}
