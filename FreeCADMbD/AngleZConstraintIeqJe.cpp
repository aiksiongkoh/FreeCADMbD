/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIeqJe.h"
#include "AngleZIeqJe.h"
#include "EndFrameq.h"

using namespace MbD;

void AngleZConstraintIeqJe::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqJe>(eFrmI, eFrmJ);
}

void AngleZConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //aFIeO = zero;
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI)
    auto aBOIp = eFrmI->aBOp();
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI)->times(0.5);
    col->equalSelfPlus(aTIeO);
}

void AngleZConstraintIeqJe::calcpGpEI()
{
    pGpEI = thezIeJe->pvaluepEI();
}

void AngleZConstraintIeqJe::calcppGpEIpEI()
{
    ppGpEIpEI = thezIeJe->ppvaluepEIpEI();
}

void AngleZConstraintIeqJe::simUpdateAll()
{
    //aG = thezIeJe - C
    AngleZConstraintIJ::simUpdateAll();
    calcpGpEI();
    calcppGpEIpEI();
}

void AngleZConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIeqJe::fillPosICError(FColDsptr col)
{
    AngleZConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void AngleZConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AngleZConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void AngleZConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AngleZConstraintIeqJe::useEquationNumbers()
{
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqEI = frmIeq->iqE();
}
