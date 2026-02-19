/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqJe.h"
#include "DirectionCosineIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqJe> DirectionCosineConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqJe>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqJe::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqcJec::With(frmIe, frmJe, axisI, axisJ);
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
    iqEI = frmIe->iqE();
}

void DirectionCosineConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
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
    ConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qEdotI = eFrmIqc->qEdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ))) * 2.0;
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void MbD::DirectionCosineConstraintIeqJe::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIeqJe::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}
