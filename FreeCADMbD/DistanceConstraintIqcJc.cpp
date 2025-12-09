/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "DistIeqcJec.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIqcJc> DistanceConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistanceConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistanceConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void DistanceConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
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

void DistanceConstraintIqcJc::calcPostDynCorrectorIteration()
{
    DistanceConstraintIJ::calcPostDynCorrectorIteration();
    pGpXI = distIeJe->pvaluepXI();
    pGpEI = distIeJe->pvaluepEI();
    ppGpXIpXI = distIeJe->ppvaluepXIpXI();
    ppGpXIpEI = distIeJe->ppvaluepXIpEI();
    ppGpEIpEI = distIeJe->ppvaluepEIpEI();
}

void DistanceConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void DistanceConstraintIqcJc::fillPosICError(FColDsptr col)
{
    DistanceConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DistanceConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void DistanceConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DistanceConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DistanceConstraintIqcJc::init_distIeJe()
{
    distIeJe = DistIeqcJec::With(eFrmI, eFrmJ);
}

void DistanceConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void DistanceConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistanceConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string DistanceConstraintIqcJc::constraintSpec()
{
    return "DistanceConstraintIJ";
}
