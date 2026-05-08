/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIeqJeq.h"
#include "DirectionCosineIeqJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqJeq> DirectionCosineConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqJeq::simUpdateAll()
{
    DirectionCosineConstraintIeqJe::simUpdateAll();
    calcpGpEJ();
    calcppGpEIpEJ();
    calcppGpEJpEJ();
}

void DirectionCosineConstraintIeqJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqJeq::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = aAijIeJe->pvaluepEJ();
}

void DirectionCosineConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = aAijIeJe->ppvaluepEIpEJ();
}

void DirectionCosineConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = aAijIeJe->ppvaluepEJpEJ();
}

void DirectionCosineConstraintIeqJeq::useEquationNumbers()
{
    DirectionCosineConstraintIeqJe::useEquationNumbers();
    iqEJ = eFrmJ->iqE();
}

void DirectionCosineConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    DirectionCosineConstraintIeqJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    DirectionCosineConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    DirectionCosineConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeqJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);

    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = eFrmIqc->qEdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
