/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIqcJc.h"
#include "AngleZIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

void AngleZConstraintIqcJc::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqcJec>(eFrmI, eFrmJ);
}

void AngleZConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto rIpIeIp = frmIeqc->rpep();
    auto pAOIppEI = frmIeqc->pAOppE();
    auto aBOIp = frmIeqc->aBOp();
    auto fpAOIppEIrIpIeIp = std::make_shared<FullColumn<double>>(4, 0.0);
    auto lampGpE = pGpEI->transpose()->times(lam);
    auto c2Torque = aBOIp->timesFullColumn(lampGpE->minusFullColumn(fpAOIppEIrIpIeIp));
    jointTorque->equalSelfPlusFullColumntimes(c2Torque, 0.5);
}

void AngleZConstraintIqcJc::calc_pGpEI()
{
    pGpEI = thezIeJe->pvaluepEI();
}

void AngleZConstraintIqcJc::calc_ppGpEIpEI()
{
    ppGpEIpEI = thezIeJe->ppvaluepEIpEI();
}

void AngleZConstraintIqcJc::calcPostDynCorrectorIteration()
{
    AngleZConstraintIJ::calcPostDynCorrectorIteration();
    this->calc_pGpEI();
    this->calc_ppGpEIpEI();
}

void AngleZConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
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
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqEI = frmIeqc->iqE();
}
