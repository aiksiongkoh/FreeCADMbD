/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIqcJc.h"
#include "AngleZIeqcJec.h"
#include "EndFrameq.h"

using namespace MbD;

void AngleZConstraintIqcJc::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqcJec>(eFrmI, eFrmJ);
}

void AngleZConstraintIqcJc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //aFIeO = zero;
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI)
    auto aBOIp = eFrmI->aBOp();
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI)->times(0.5);
    col->equalSelfPlus(aTIeO);
}

void AngleZConstraintIqcJc::calcpGpEI()
{
    pGpEI = thezIeJe->pvaluepEI();
}

void AngleZConstraintIqcJc::calcppGpEIpEI()
{
    ppGpEIpEI = thezIeJe->ppvaluepEIpEI();
}

void AngleZConstraintIqcJc::simUpdateAll()
{
    //aG = thezIeJe - C
    AngleZConstraintIJ::simUpdateAll();
    calcpGpEI();
    calcppGpEIpEI();
}

void AngleZConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIqcJc::fillPosICError(FColDsptr col)
{
    AngleZConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void AngleZConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AngleZConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void AngleZConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AngleZConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqEI = frmIeqc->iqE();
}
