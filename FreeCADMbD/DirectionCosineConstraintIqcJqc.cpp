/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIqcJqc.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIqcJqc> DirectionCosineConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIqcJqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIqcJqc::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqcJeqc::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    DirectionCosineConstraintIqcJc::calcPostDynCorrectorIteration();
    auto aAijIeqJqe = std::static_pointer_cast<DirectionCosineIeqcJeqc>(aAijIeJe);
    pGpEJ = aAijIeqJqe->pAijIeJepEJ;
    ppGpEIpEJ = aAijIeqJqe->ppAijIeJepEIpEJ;
    ppGpEJpEJ = aAijIeqJqe->ppAijIeJepEJpEJ;
}

void DirectionCosineConstraintIqcJqc::useEquationNumbers()
{
    DirectionCosineConstraintIqcJc::useEquationNumbers();
    iqEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->iqE();
}

void DirectionCosineConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    DirectionCosineConstraintIqcJc::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    DirectionCosineConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    DirectionCosineConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = eFrmIqc->qEdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ))) * 2.0;
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
