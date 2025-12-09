/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJeqcIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIqcJqc> DistancexyConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistancexyConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIqcJqc::calc_pGpXJ()
{
    pGpXJ = (xIeJeIe->pvaluepXJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXJ()->times(yIeJeIe->value())));
    pGpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_pGpEJ()
{
    pGpEJ = (xIeJeIe->pvaluepEJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEJ()->times(yIeJeIe->value())));
    pGpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpXIpXJ()
{
    //xIeJeIe ppvaluepXIpXJ = 0
    //yIeJeIe ppvaluepXIpXJ = 0
    ppGpXIpXJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpXIpXJ = ppGpXIpXJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpXIpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpEIpXJ()
{
    ppGpEIpXJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(xIeJeIe->ppvaluepEIpXJ()->times(xIeJeIe->value()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->ppvaluepEIpXJ()->times(yIeJeIe->value()));
    ppGpEIpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpXJpXJ()
{
    //xIeJeIe ppvaluepXJpXJ = 0
    //yIeJeIe ppvaluepXJpXJ = 0
    ppGpXJpXJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
    ppGpXJpXJ = ppGpXJpXJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
    ppGpXJpXJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpXIpEJ()
{
    //xIeJeIe ppvaluepXIpEJ = 0
    //yIeJeIe ppvaluepXIpEJ = 0
    ppGpXIpEJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpXIpEJ = ppGpXIpEJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpXIpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpEIpEJ()
{
    ppGpEIpEJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(xIeJeIe->ppvaluepEIpEJ()->times(xIeJeIe->value()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->ppvaluepEIpEJ()->times(yIeJeIe->value()));
    ppGpEIpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpXJpEJ()
{
    //xIeJeIe ppvaluepXJpEJ = 0
    //yIeJeIe ppvaluepXJpEJ = 0
    ppGpXJpEJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpXJpEJ = ppGpXJpEJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpXJpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calc_ppGpEJpEJ()
{
    ppGpEJpEJ = (xIeJeIe->pvaluepEJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(xIeJeIe->ppvaluepEJpEJ()->times(xIeJeIe->value()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->pvaluepEJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
    ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->ppvaluepEJpEJ()->times(yIeJeIe->value()));
    ppGpEJpEJ->magnifySelf(2.0);
}

void DistancexyConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    DistancexyConstraintIqcJc::calcPostDynCorrectorIteration();
    calc_pGpXJ();
    calc_pGpEJ();
    calc_ppGpXIpXJ();
    calc_ppGpEIpXJ();
    calc_ppGpXJpXJ();
    calc_ppGpXIpEJ();
    calc_ppGpEIpEJ();
    calc_ppGpXJpEJ();
    calc_ppGpEJpEJ();
}

void DistancexyConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    DistancexyConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qXdotI = frmIeqc->qXdot();
    auto qEdotI = frmIeqc->qEdot();
    auto qXdotJ = frmJeqc->qXdot();
    auto qEdotJ = frmJeqc->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(frmJeqc->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += qXdotJ->transposeTimesFullColumn(ppGpXJpXJ->timesFullColumn(qXdotJ));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qXdotJ->transposeTimesFullColumn(ppGpXJpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void DistancexyConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    DistancexyConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DistancexyConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    DistancexyConstraintIqcJc::fillPosICJacob(mat);
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

void DistancexyConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    DistancexyConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DistancexyConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    DistancexyConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DistancexyConstraintIqcJqc::init_xyIeJeIe()
{
    xIeJeIe = DispCompIeqcJeqcIe::With(eFrmI, eFrmJ, 0);
    yIeJeIe = DispCompIeqcJeqcIe::With(eFrmI, eFrmJ, 1);
}

void DistancexyConstraintIqcJqc::useEquationNumbers()
{
    DistancexyConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJ = frmJeqc->iqX();
    iqEJ = frmJeqc->iqE();
}

void DistancexyConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    DistancexyConstraintIqcJc::fillpFpy(mat);
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

void DistancexyConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    DistancexyConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
