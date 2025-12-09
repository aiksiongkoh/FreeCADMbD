/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "AngleZIeqcJec.h"
#include "DispCompIeqcJecIe.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIqcJc> RackPinConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<RackPinConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIqcJc::initialize()
{
    RackPinConstraintIJ::initialize();
    pGpXI = FullRow<double>::With(3);
    pGpEI = FullRow<double>::With(4);
    ppGpXIpEI = FullMatrix<double>::With(3, 4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void RackPinConstraintIqcJc::initxIeJeIe()
{
    xIeJeIe = DispCompIeqcJecIe::With(eFrmI, eFrmJ, 0);
}

void RackPinConstraintIqcJc::initthezIeJe()
{
    thezIeJe = AngleZIeqcJec::With(eFrmI, eFrmJ);
}

void RackPinConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void RackPinConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
    auto cForceT = pGpXI->times(lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto rIpIeIp = frmIeqc->rpep();
    auto pAOIppEI = frmIeqc->pAOppE();
    auto aBOIp = frmIeqc->aBOp();
    auto fpAOIppEIrIpIeIp = std::make_shared<FullColumn<double>>(4, 0.0);
    for (size_t i = 0; i < 4; i++)
    {
        auto dum = cForceT->timesFullColumn(pAOIppEI->at(i)->timesFullColumn(rIpIeIp));
        fpAOIppEIrIpIeIp->atiput(i, dum);
    }
    auto lampGpE = pGpEI->transpose()->times(lam);
    auto c2Torque = aBOIp->timesFullColumn(lampGpE->minusFullColumn(fpAOIppEIrIpIeIp));
    jointTorque->equalSelfPlusFullColumntimes(c2Torque, 0.5);
}

void RackPinConstraintIqcJc::calc_pGpEI()
{
    pGpEI = xIeJeIe->pvaluepEI()->plusFullRow(thezIeJe->pvaluepEI()->times(pitchRadius));
}

void RackPinConstraintIqcJc::calc_pGpXI()
{
    pGpXI = xIeJeIe->pvaluepXI();
}

void RackPinConstraintIqcJc::calc_ppGpEIpEI()
{
    ppGpEIpEI = xIeJeIe->ppvaluepEIpEI()
            ->plusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitchRadius));
}

void RackPinConstraintIqcJc::calc_ppGpXIpEI()
{
    ppGpXIpEI = xIeJeIe->ppvaluepXIpEI();
}

void RackPinConstraintIqcJc::calcPostDynCorrectorIteration()
{
    RackPinConstraintIJ::calcPostDynCorrectorIteration();
    calc_pGpXI();
    calc_pGpEI();
    calc_ppGpXIpEI();
    calc_ppGpEIpEI();
}

void RackPinConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void RackPinConstraintIqcJc::fillPosICError(FColDsptr col)
{
    RackPinConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void RackPinConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void RackPinConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void RackPinConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void RackPinConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void RackPinConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void RackPinConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}
