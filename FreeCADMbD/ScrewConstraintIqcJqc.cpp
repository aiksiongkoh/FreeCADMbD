/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>
#include <numbers>

#include "ScrewConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJeqcIe.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIqcJqc> ScrewConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ScrewConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIqcJqc::initialize()
{
    ScrewConstraintIqcJc::initialize();
    pGpXJ = FullRow<double>::With(3);
    pGpEJ = FullRow<double>::With(4);
    ppGpEIpXJ = FullMatrix<double>::With(4, 3);
    ppGpEIpEJ = FullMatrix<double>::With(4, 4);
    ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

void ScrewConstraintIqcJqc::initzIeJeIe()
{
    zIeJeIe = DispCompIeqcJeqcIe::With(eFrmI, eFrmJ, 2);
}

void ScrewConstraintIqcJqc::initthezIeJe()
{
    thezIeJe = AngleZIeqcJeqc::With(eFrmI, eFrmJ);
}

void ScrewConstraintIqcJqc::calc_pGpEJ()
{
    pGpEJ = zIeJeIe->pvaluepEJ()->times(2.0 * std::numbers::pi)->minusFullRow(thezIeJe->pvaluepEJ()->times(pitch));
}

void ScrewConstraintIqcJqc::calc_pGpXJ()
{
    pGpXJ = zIeJeIe->pvaluepXJ()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIqcJqc::calc_ppGpEIpEJ()
{
    ppGpEIpEJ = zIeJeIe->ppvaluepEIpEJ()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitch));
}

void ScrewConstraintIqcJqc::calc_ppGpEIpXJ()
{
    ppGpEIpXJ = zIeJeIe->ppvaluepEIpXJ()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIqcJqc::calc_ppGpEJpEJ()
{
    ppGpEJpEJ = zIeJeIe->ppvaluepEJpEJ()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitch));
}

void ScrewConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    ScrewConstraintIqcJc::calcPostDynCorrectorIteration();
    calc_pGpXJ();
    calc_pGpEJ();
    calc_ppGpEIpXJ();
    calc_ppGpEIpEJ();
    calc_ppGpEJpEJ();
}

void ScrewConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    ScrewConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = frmIeqc->qEdot();
    auto qXdotJ = frmJeqc->qXdot();
    auto qEdotJ = frmJeqc->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(frmJeqc->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void ScrewConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    ScrewConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void ScrewConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    ScrewConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void ScrewConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    ScrewConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void ScrewConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    ScrewConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void ScrewConstraintIqcJqc::useEquationNumbers()
{
    ScrewConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJ = frmJeqc->iqX();
    iqEJ = frmJeqc->iqE();
}

void ScrewConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    ScrewConstraintIqcJc::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void ScrewConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    ScrewConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
