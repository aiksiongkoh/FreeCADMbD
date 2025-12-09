/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <cmath>
#include <numbers>

#include "ScrewConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJecIe.h"
#include "AngleZIeqcJec.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIqcJc> ScrewConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ScrewConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIqcJc::initialize()
{
    ScrewConstraintIJ::initialize();
    pGpXI = FullRow<double>::With(3);
    pGpEI = FullRow<double>::With(4);
    ppGpXIpEI = FullMatrix<double>::With(3, 4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void ScrewConstraintIqcJc::initzIeJeIe()
{
    zIeJeIe = DispCompIeqcJecIe::With(eFrmI, eFrmJ, 2);
}

void ScrewConstraintIqcJc::initthezIeJe()
{
    thezIeJe = AngleZIeqcJec::With(eFrmI, eFrmJ);
}

void ScrewConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void ScrewConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
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

void ScrewConstraintIqcJc::calc_pGpEI()
{
    pGpEI = zIeJeIe->pvaluepEI()->times(2.0 * std::numbers::pi)->minusFullRow(thezIeJe->pvaluepEI()->times(pitch));
}

void ScrewConstraintIqcJc::calc_pGpXI()
{
    pGpXI = zIeJeIe->pvaluepXI()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIqcJc::calc_ppGpEIpEI()
{
    ppGpEIpEI = zIeJeIe->ppvaluepEIpEI()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitch));
}

void ScrewConstraintIqcJc::calc_ppGpXIpEI()
{
    ppGpXIpEI = zIeJeIe->ppvaluepXIpEI()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIqcJc::calcPostDynCorrectorIteration()
{
    ScrewConstraintIJ::calcPostDynCorrectorIteration();
    calc_pGpXI();
    calc_pGpEI();
    calc_ppGpXIpEI();
    calc_ppGpEIpEI();
}

void ScrewConstraintIqcJc::fillAccICIterError(FColDsptr col)
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

void ScrewConstraintIqcJc::fillPosICError(FColDsptr col)
{
    ScrewConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void ScrewConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void ScrewConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void ScrewConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void ScrewConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void ScrewConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ScrewConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string ScrewConstraintIqcJc::constraintSpec()
{
    return "ScrewConstraintIJ";
}
