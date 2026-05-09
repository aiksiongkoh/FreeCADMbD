/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqJe.h"
#include "DirectionCosineIeqJe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqJe> DirectionCosineConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqJe>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqJe::simUpdateAll()
{
    DirectionCosineConstraintIeJe::simUpdateAll();
    calcpGpEI();
    calcppGpEIpEI();
}

void DirectionCosineConstraintIeqJe::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqJe::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIeqJe::calcpGpEI()
{
    pGpEI = aAijIeJe->pvaluepEI();
}

void DirectionCosineConstraintIeqJe::calcppGpEIpEI()
{
    ppGpEIpEI = aAijIeJe->ppvaluepEIpEI();
}

void DirectionCosineConstraintIeqJe::useEquationNumbers()
{
    DirectionCosineConstraintIeJe::useEquationNumbers();
    iqEI = eFrmI->iqE();
}

void DirectionCosineConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DirectionCosineConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DirectionCosineConstraintIeqJe::fillPosICError(FColDsptr col)
{
    DirectionCosineConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DirectionCosineConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DirectionCosineConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DirectionCosineConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DirectionCosineConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qEdotI = eFrmIeq->qEdot();
    double sum = pGpEI->timesFullColumn(eFrmIeq->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void DirectionCosineConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //aFIeO = zero
    //aTIeO = 0.5 * aBOIp * lam * pGpEI
    auto aBOIp = eFrmI->aBOp();
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI)->times(0.5);
    col->equalSelfPlus(aTIeO);
}
