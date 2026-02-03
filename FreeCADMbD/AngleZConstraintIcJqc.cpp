/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIcJqc.h"
#include "AngleZIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

void AngleZConstraintIcJqc::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqcJeqc>(eFrmI, eFrmJ);
}

void AngleZConstraintIcJqc::calcpGpEJ()
{
    pGpEJ = thezIeJe->pvaluepEJ();
}

void AngleZConstraintIcJqc::calcppGpEJpEJ()
{
    ppGpEJpEJ = thezIeJe->ppvaluepEJpEJ();
}

void MbD::AngleZConstraintIcJqc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeqc
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

void AngleZConstraintIcJqc::simUpdateAll()
{
    //aG = thezIeJe - C
    AngleZConstraintIJ::simUpdateAll();
    this->calcpGpEJ();
    this->calcppGpEJpEJ();
}

void AngleZConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
    AngleZConstraintIJ::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = frmIeqc->qEdot();
    auto qXdotJ = frmJeqc->qXdot();
    auto qEdotJ = frmJeqc->qEdot();
    double sum = 0.0;
    sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIcJqc::fillPosICError(FColDsptr col)
{
    AngleZConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AngleZConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AngleZConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AngleZConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
    AngleZConstraintIJ::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AngleZConstraintIcJqc::useEquationNumbers()
{
    AngleZConstraintIJ::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqEJ = frmJeqc->iqE();
}
