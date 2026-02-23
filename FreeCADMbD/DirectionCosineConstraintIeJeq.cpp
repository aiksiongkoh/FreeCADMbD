/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeJeq.h"
#include "DirectionCosineIecJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeJeq> DirectionCosineConstraintIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeJeq::simUpdateAll()
{
    DirectionCosineConstraintIeJe::simUpdateAll();
    calcpGpEJ();
    calcppGpEJpEJ();
}

void DirectionCosineConstraintIeJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIecJeqc::With(frmIe, frmJe, axisI, axisJ);
}

void DirectionCosineConstraintIeJeq::calcpGpEJ()
{
    pGpEJ = aAijIeJe->pvaluepEJ();
}

void DirectionCosineConstraintIeJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = aAijIeJe->ppvaluepEJpEJ();
}

void DirectionCosineConstraintIeJeq::useEquationNumbers()
{
    DirectionCosineConstraintIeJe::useEquationNumbers();
    iqEJ = frmJe->iqE();
}

void DirectionCosineConstraintIeJeq::fillpFpy(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeJeq::fillpFpydot(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::DirectionCosineConstraintIeJeq::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ = zero
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ)
    //aTIeO = rJeIeO cross aFJeO - aTJeO
    //aTIeO = -aTJeO

    auto aBOJp = frmJe->aBOp();
    auto lampGpEJ = pGpEJ->transpose()->times(lam);  //lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ)->times(0.5);
    auto aTIeO = aTJeO->negated();
    col->equalSelfPlus(aTIeO);
}

void DirectionCosineConstraintIeJeq::fillPosICError(FColDsptr col)
{
    DirectionCosineConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIeJeq::fillPosICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeJeq::fillPosKineJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeJeq::fillVelICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeJeq::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qEdotJ = frmJeq->qEdot();
    double sum = pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
