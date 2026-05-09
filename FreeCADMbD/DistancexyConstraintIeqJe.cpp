/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIeqJe.h"
#include "EndFrameq.h"
//#include "EndFrame.h"
#include "DispCompiIeJeIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIeqJe> DistancexyConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistancexyConstraintIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void DistancexyConstraintIeqJe::addToJointTorqueI(FColDsptr col)
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

void DistancexyConstraintIeqJe::simUpdateAll()
{
    //aG = xIeJeIe^2 + yIeJeIe^2 - C^2;
    DistancexyConstraintIeJe::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpXI();
    calcppGpXIpEI();
    calcppGpEIpEI();
}

void DistancexyConstraintIeqJe::calcpGpEI()
{
    pGpEI = (xIeJeIe->pvaluepEI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEI()->times(yIeJeIe->value())));
    pGpEI->magnifySelf(2.0);
}

void DistancexyConstraintIeqJe::calcpGpXI()
{
    pGpXI = (xIeJeIe->pvaluepXI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXI()->times(yIeJeIe->value())));
    pGpXI->magnifySelf(2.0);
}

void DistancexyConstraintIeqJe::calcppGpEIpEI()
{
    ppGpEIpEI = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(xIeJeIe->ppvaluepEIpEI()->times(xIeJeIe->value()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->ppvaluepEIpEI()->times(yIeJeIe->value()));
    ppGpEIpEI->magnifySelf(2.0);
}

void DistancexyConstraintIeqJe::calcppGpXIpEI()
{
    ppGpXIpEI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(xIeJeIe->ppvaluepXIpEI()->times(xIeJeIe->value()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->ppvaluepXIpEI()->times(yIeJeIe->value()));
    ppGpXIpEI->magnifySelf(2.0);
}

void DistancexyConstraintIeqJe::calcppGpXIpXI()
{
    //xIeJeIe ppvaluepXIpXI = 0
    //yIeJeIe ppvaluepXIpXI = 0
    ppGpXIpXI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXI()));
    ppGpXIpXI = ppGpXIpXI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXI()));
    ppGpXIpXI->magnifySelf(2.0);
}

void DistancexyConstraintIeqJe::fillAccICIterError(FColDsptr col)
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

void DistancexyConstraintIeqJe::fillPosICError(FColDsptr col)
{
    DistancexyConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DistancexyConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
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

void DistancexyConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DistancexyConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DistancexyConstraintIeqJe::useEquationNumbers()
{
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqXI = frmIeq->iqX();
    iqEI = frmIeq->iqE();
}

void DistancexyConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistancexyConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string DistancexyConstraintIeqJe::constraintSpec()
{
    return "DistancexyConstraintIeJe";
}


