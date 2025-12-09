/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIqcJc.h"
#include "DirectionCosineIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIqcJc> DirectionCosineConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIqcJc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIqcJc::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqcJec::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIqcJc::calcPostDynCorrectorIteration()
{
    DirectionCosineConstraintIJ::calcPostDynCorrectorIteration();
    auto aAijIeqJe = std::static_pointer_cast<DirectionCosineIeqcJec>(aAijIeJe);
    pGpEI = aAijIeqJe->pAijIeJepEI;
    ppGpEIpEI = aAijIeqJe->ppAijIeJepEIpEI;
}

void DirectionCosineConstraintIqcJc::useEquationNumbers()
{
    iqEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->iqE();
}

void DirectionCosineConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}


void DirectionCosineConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string DirectionCosineConstraintIqcJc::constraintSpec()
{
    return "DirectionCosineConstraintIJ";
}

void DirectionCosineConstraintIqcJc::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DirectionCosineConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DirectionCosineConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DirectionCosineConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DirectionCosineConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVector(iqEI, pGpEI->times(lam));
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void DirectionCosineConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
    auto aBOIp = eFrmI->aBOp();
    auto lampGpE = pGpEI->transpose()->times(lam);
    auto c2Torque = aBOIp->timesFullColumn(lampGpE);
    jointTorque->equalSelfPlusFullColumntimes(c2Torque, 0.5);
}
