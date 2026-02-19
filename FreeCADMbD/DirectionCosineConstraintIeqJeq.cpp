/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqJeq.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqJeq> DirectionCosineConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqcJeqc::With(frmIe, frmJe, axisI, axisJ);
}

void MbD::DirectionCosineConstraintIeqJeq::calcpGpEJ()
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
    iqEJ = frmJe->iqE();
}

void DirectionCosineConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
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
    ConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJeq::fillAccICIterError(FColDsptr col)
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

void MbD::DirectionCosineConstraintIeqJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIeqJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}
