/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "OrbitAngleZIeqcJec.h"

using namespace MbD;

std::shared_ptr<GearConstraintIqcJc> GearConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<GearConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void GearConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
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

void GearConstraintIqcJc::calc_pGpEI()
{
    pGpEI = orbitJeIe->pvaluepEJ()->plusFullRow(orbitIeJe->pvaluepEI()->times(ratio()));
}

void GearConstraintIqcJc::calc_pGpXI()
{
    pGpXI = orbitJeIe->pvaluepXJ()->plusFullRow(orbitIeJe->pvaluepXI()->times(ratio()));
}

void GearConstraintIqcJc::calc_ppGpEIpEI()
{
    ppGpEIpEI = orbitJeIe->ppvaluepEJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepEIpEI()->times(ratio()));
}

void GearConstraintIqcJc::calc_ppGpXIpEI()
{
    ppGpXIpEI = orbitJeIe->ppvaluepXJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpEI()->times(ratio()));
}

void GearConstraintIqcJc::calc_ppGpXIpXI()
{
    ppGpXIpXI = orbitJeIe->ppvaluepXJpXJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpXI()->times(ratio()));
}

void GearConstraintIqcJc::calcPostDynCorrectorIteration()
{
    GearConstraintIJ::calcPostDynCorrectorIteration();
    calc_pGpXI();
    calc_pGpEI();
    calc_ppGpXIpXI();
    calc_ppGpXIpEI();
    calc_ppGpEIpEI();
}

void GearConstraintIqcJc::fillAccICIterError(FColDsptr col)
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

void GearConstraintIqcJc::fillPosICError(FColDsptr col)
{
    GearConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void GearConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void GearConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void GearConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void GearConstraintIqcJc::initorbitsIJ()
{
    orbitIeJe = OrbitAngleZIeqcJec::With(eFrmI, eFrmJ);
    orbitJeIe = OrbitAngleZIeqcJec::With(eFrmJ, eFrmI);
}

void GearConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void GearConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void GearConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string GearConstraintIqcJc::constraintSpec()
{
    return "GearConstraintIqcJc";
}
