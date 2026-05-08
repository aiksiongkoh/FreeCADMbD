/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>
#include <numbers>

#include "ScrewConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "DispCompiIeJeIe.h"
#include "AngleZIeqJeq.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIeqJeq> ScrewConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ScrewConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIeqJeq::initialize()
{
    ScrewConstraintIeqJe::initialize();
    pGpXJ = FullRow<double>::With(3);
    pGpEJ = FullRow<double>::With(4);
    ppGpEIpXJ = FullMatrix<double>::With(4, 3);
    ppGpEIpEJ = FullMatrix<double>::With(4, 4);
    ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

void ScrewConstraintIeqJeq::initzIeJeIe()
{
    zIeJeIe = DispCompiIeJeIe::With(eFrmI, eFrmJ, 2);
    zIeJeIe->owner = this;
}

void ScrewConstraintIeqJeq::initthezIeJe()
{
    thezIeJe = AngleZIeqJeq::With(eFrmI, eFrmJ);
}

void ScrewConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = zIeJeIe->pvaluepEJ()->times(2.0 * std::numbers::pi)->minusFullRow(thezIeJe->pvaluepEJ()->times(pitch));
}

void ScrewConstraintIeqJeq::calcpGpXJ()
{
    pGpXJ = zIeJeIe->pvaluepXJ()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = zIeJeIe->ppvaluepEIpEJ()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitch));
}

void ScrewConstraintIeqJeq::calcppGpEIpXJ()
{
    ppGpEIpXJ = zIeJeIe->ppvaluepEIpXJ()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = zIeJeIe->ppvaluepEJpEJ()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitch));
}

void ScrewConstraintIeqJeq::simUpdateAll()
{
    ScrewConstraintIeqJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpEJpEJ();
}

void ScrewConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    ScrewConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void ScrewConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    ScrewConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void ScrewConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    ScrewConstraintIeqJe::fillPosICJacob(mat);
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

void ScrewConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    ScrewConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void ScrewConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    ScrewConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void ScrewConstraintIeqJeq::useEquationNumbers()
{
    ScrewConstraintIeqJe::useEquationNumbers();
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqXJ = frmJeq->iqX();
    iqEJ = frmJeq->iqE();
}

void ScrewConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    ScrewConstraintIeqJe::fillpFpy(mat);
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

void ScrewConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    ScrewConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
