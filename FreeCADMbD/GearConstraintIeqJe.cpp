/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIeqJe.h"
#include "EndFrameq.h"
#include "OrbitAngleZIeqJe.h"

using namespace MbD;

std::shared_ptr<GearConstraintIeqJe> GearConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<GearConstraintIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void GearConstraintIeqJe::addToJointTorqueI(FColDsptr col)
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

void GearConstraintIeqJe::calcpGpEI()
{
    pGpEI = orbitJeIe->pvaluepEJ()->plusFullRow(orbitIeJe->pvaluepEI()->times(ratio()));
}

void GearConstraintIeqJe::calcpGpXI()
{
    pGpXI = orbitJeIe->pvaluepXJ()->plusFullRow(orbitIeJe->pvaluepXI()->times(ratio()));
}

void GearConstraintIeqJe::calcppGpEIpEI()
{
    ppGpEIpEI = orbitJeIe->ppvaluepEJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepEIpEI()->times(ratio()));
}

void GearConstraintIeqJe::calcppGpXIpEI()
{
    ppGpXIpEI = orbitJeIe->ppvaluepXJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpEI()->times(ratio()));
}

void GearConstraintIeqJe::calcppGpXIpXI()
{
    ppGpXIpXI = orbitJeIe->ppvaluepXJpXJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpXI()->times(ratio()));
}

void GearConstraintIeqJe::simUpdateAll()
{
    GearConstraintIJ::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpXI();
    calcppGpXIpEI();
    calcppGpEIpEI();
}

void GearConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void GearConstraintIeqJe::fillPosICError(FColDsptr col)
{
    GearConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void GearConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
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

void GearConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void GearConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void GearConstraintIeqJe::useEquationNumbers()
{
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqXI = frmIeq->iqX();
    iqEI = frmIeq->iqE();
}

void GearConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void GearConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string GearConstraintIeqJe::constraintSpec()
{
    return "GearConstraintIeqJe";
}
