/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIeJeq.h"
#include "AngleZIeqJeq.h"
#include "EndFrameq.h"

using namespace MbD;

void AngleZConstraintIeJeq::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqJeq>(eFrmI, eFrmJ);
}

void AngleZConstraintIeJeq::calcpGpEJ()
{
    pGpEJ = thezIeJe->pvaluepEJ();
}

void AngleZConstraintIeJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = thezIeJe->ppvaluepEJpEJ();
}

void AngleZConstraintIeJeq::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIe does not have q, we use frmJeq
    //aFJeO = lam * pGpXJ = zero
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ)
    //aTIeO = rJeIeO cross aFJeO - aTJeO
    //aTIeO = -aTJeO

    auto aBOJp = eFrmJ->aBOp();
    auto lampGpEJ = pGpEJ->transpose()->times(lam);  //lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ)->times(0.5);
    auto aTIeO = aTJeO->negated();
    col->equalSelfPlus(aTIeO);
}

void AngleZConstraintIeJeq::simUpdateAll()
{
    //aG = thezIeJe - C
    AngleZConstraintIJ::simUpdateAll();
    calcpGpEJ();
    calcppGpEJpEJ();
}

void AngleZConstraintIeJeq::fillAccICIterError(FColDsptr col)
{
    AngleZConstraintIJ::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIeJeq::fillPosICError(FColDsptr col)
{
    AngleZConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AngleZConstraintIeJeq::fillPosICJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AngleZConstraintIeJeq::fillPosKineJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AngleZConstraintIeJeq::fillVelICJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AngleZConstraintIeJeq::useEquationNumbers()
{
    AngleZConstraintIJ::useEquationNumbers();
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqEJ = frmJeq->iqE();
}
