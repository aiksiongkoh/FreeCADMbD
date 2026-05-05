/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIeJeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeJeq> AtPointConstraintIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeJeq::simUpdateAll()
{
    AtPointConstraintIeJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEJpEJ();
}

void AtPointConstraintIeJeq::initializeGlobally()
{
    AtPointConstraintIeJe::initializeGlobally();
}

void MbD::AtPointConstraintIeJeq::calcpGpXJ()
{
    // pGpXJ = [I];
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    pGpXJ = prIeJeOpXJ->at(axis);
}

void MbD::AtPointConstraintIeJeq::calcpGpEJ()
{
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    pGpEJ = prIeJeOpEJ->at(axis);
}

void MbD::AtPointConstraintIeJeq::calcppGpEJpEJ()
{
    // ppGpEJpEJ is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEJpEJ = dispIeJeO->getppCompipEJpEJ(axis);
}

void MbD::AtPointConstraintIeJeq::initializeLocally()
{
    AtPointConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeJeq::useEquationNumbers()
{
    AtPointConstraintIeJe::useEquationNumbers();
    iqXJ = eFrmJ->iqX();
    iqEJ = eFrmJ->iqE();
}

void AtPointConstraintIeJeq::fillpFpy(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeJeq::fillpFpydot(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::AtPointConstraintIeJeq::addToJointForceI(FColDsptr col)
{
    // aFIeO = lam * pGpXI
    // frmIec does not have q, we use frmJeq
    // aFJeO = lam * pGpXJ
    // aFIeO = -aFJeO
    auto aFJeO = pGpXJ->transpose()->times(lam);
    col->equalSelfMinus(aFJeO);
}

void MbD::AtPointConstraintIeJeq::addToJointTorqueI(FColDsptr col)
{
    // aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    // frmIe does not have q, we use frmJeq
    // aFJeO = lam * pGpXJ
    // aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    // aTJeO = 0.5 * aBOJp * (lam * pGpEJ - p(aAOJp * rJpJeJp)pEJT * aFJeO)
    // aTJeO = 0.5 * aBOJp * (lam * pGpEJ - (pAOJppEJ * rJpJeJp)T * aFJeO)
    // aTJeO = rIeJeO cross aFIeO - aTIeO
    // aTIeO = rJeIeO cross aFJeO - aTJeO

    auto aFJeOT = pGpXJ->times(lam);
    auto rJpJeJp = eFrmJ->rpep();
    auto pAOJppEJ = eFrmJ->pAOppE();
    auto aBOJp = eFrmJ->aBOp();
    auto prOJeOpEJTaFJeO = std::make_shared<FullColumn<double>>(4, 0.0); // prOJeOpEJT * aFJeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOJeOpEJTaFJeOi = aFJeOT->timesFullColumn(pAOJppEJ->at(i)->timesFullColumn(rJpJeJp));
        prOJeOpEJTaFJeO->atiput(i, prOJeOpEJTaFJeOi);
    }
    auto lampGpEJ = pGpEJ->transpose()->times(lam); // lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ->minusFullColumn(prOJeOpEJTaFJeO))->times(0.5);
    auto rJeIeO = getrIeJeO()->negated();
    auto aFJeO = aFJeOT->transpose();
    auto aTIeO = rJeIeO->cross(aFJeO)->minusFullColumn(aTJeO);
    col->equalSelfPlus(aTIeO);
}

void AtPointConstraintIeJeq::fillPosICError(FColDsptr col)
{
    AtPointConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIeJeq::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeJeq::fillVelICJacob(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::AtPointConstraintIeJeq::fillPosKineJacob(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AtPointConstraintIeJeq::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
