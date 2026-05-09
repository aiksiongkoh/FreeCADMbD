/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistanceConstraintIeqJe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIeqJe> DistanceConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistanceConstraintIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistanceConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void DistanceConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    auto aFIeOT = pGpXI->times(lam);
    auto rIpIeIp = eFrmI->rpep();
    auto pAOIppEI = eFrmI->pAOppE();
    auto aBOIp = eFrmI->aBOp();
    auto prOIeOpEITaFIeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOIeOpEIT * aFIeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOIeOpEITaFIeOi = aFIeOT->timesFullColumn(pAOIppEI->at(i)->timesFullColumn(rIpIeIp));
        prOIeOpEITaFIeO->atiput(i, prOIeOpEITaFIeOi);
    }
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI->minusFullColumn(prOIeOpEITaFIeO))->times(0.5);
    col->equalSelfPlus(aTIeO);
}

void DistanceConstraintIeqJe::simUpdateAll()
{
    //aG = rIeJe - C;
    DistanceConstraintIeJe::simUpdateAll();
    pGpXI = distIeJe->pvaluepXI();
    pGpEI = distIeJe->pvaluepEI();
    ppGpXIpXI = distIeJe->ppvaluepXIpXI();
    ppGpXIpEI = distIeJe->ppvaluepXIpEI();
    ppGpEIpEI = distIeJe->ppvaluepEIpEI();
}

void DistanceConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIeq->qXdot();
    auto qEdotI = eFrmIeq->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIeq->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIeq->qEddot());
    sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void DistanceConstraintIeqJe::fillPosICError(FColDsptr col)
{
    DistanceConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DistanceConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistanceConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DistanceConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DistanceConstraintIeqJe::useEquationNumbers()
{
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqXI = frmIeq->iqX();
    iqEI = frmIeq->iqE();
}

void DistanceConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistanceConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string DistanceConstraintIeqJe::constraintSpec()
{
    return "DistanceConstraintIeJe";
}
