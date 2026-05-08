/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "DispCompiIeJeIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIeqJeq> DistancexyConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistancexyConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIeqJeq::calcpGpXJ()
{
    pGpXJ = (xIeJeIe->pvaluepXJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXJ()->times(yIeJeIe->value())));
    pGpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = (xIeJeIe->pvaluepEJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEJ()->times(yIeJeIe->value())));
    pGpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpXIpXJ()
{
    //xIeJeIe ppvaluepXIpXJ = 0
    //yIeJeIe ppvaluepXIpXJ = 0
    ppGpXIpXJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpXIpXJ = ppGpXIpXJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpXIpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpEIpXJ()
{
    ppGpEIpXJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(xIeJeIe->ppvaluepEIpXJ()->times(xIeJeIe->value()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->ppvaluepEIpXJ()->times(yIeJeIe->value()));
    ppGpEIpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpXJpXJ()
{
    //xIeJeIe ppvaluepXJpXJ = 0
    //yIeJeIe ppvaluepXJpXJ = 0
    ppGpXJpXJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpXJpXJ = ppGpXJpXJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpXJpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpXIpEJ()
{
    //xIeJeIe ppvaluepXIpEJ = 0
    //yIeJeIe ppvaluepXIpEJ = 0
    ppGpXIpEJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpXIpEJ = ppGpXIpEJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpXIpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(xIeJeIe->ppvaluepEIpEJ()->times(xIeJeIe->value()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->ppvaluepEIpEJ()->times(yIeJeIe->value()));
    ppGpEIpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpXJpEJ()
{
    //xIeJeIe ppvaluepXJpEJ = 0
    //yIeJeIe ppvaluepXJpEJ = 0
    ppGpXJpEJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpXJpEJ = ppGpXJpEJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpXJpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = (xIeJeIe->pvaluepEJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(xIeJeIe->ppvaluepEJpEJ()->times(xIeJeIe->value()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->pvaluepEJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->ppvaluepEJpEJ()->times(yIeJeIe->value()));
    ppGpEJpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIeqJeq::simUpdateAll()
{
    //aG = xIeJeIe^2 + yIeJeIe^2 - C^2;
    DistancexyConstraintIeqJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpXIpXJ();
    calcppGpEIpXJ();
    calcppGpXJpXJ();
    calcppGpXIpEJ();
    calcppGpEIpEJ();
    calcppGpXJpEJ();
    calcppGpEJpEJ();
}

void DistancexyConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    DistancexyConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += qXdotJ->transposeTimesFullColumn(ppGpXJpXJ->timesFullColumn(qXdotJ));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qXdotJ->transposeTimesFullColumn(ppGpXJpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void DistancexyConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    DistancexyConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DistancexyConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    DistancexyConstraintIeqJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
    mat->atijplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DistancexyConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    DistancexyConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DistancexyConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    DistancexyConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DistancexyConstraintIeqJeq::init_xyIeJeIe()
{
    xIeJeIe = DispCompiIeJeIe::With(eFrmI, eFrmJ, 0);
    xIeJeIe->owner = this;
    yIeJeIe = DispCompiIeJeIe::With(eFrmI, eFrmJ, 1);
    yIeJeIe->owner = this;
}

void DistancexyConstraintIeqJeq::useEquationNumbers()
{
    DistancexyConstraintIeqJe::useEquationNumbers();
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqXJ = frmJeq->iqX();
    iqEJ = frmJeq->iqE();
}

void DistancexyConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    DistancexyConstraintIeqJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
    mat->atijplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DistancexyConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    DistancexyConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
