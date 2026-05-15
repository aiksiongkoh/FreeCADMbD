/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "DispCompiIeJeIe.h"
#include "AngleZIeqJeq.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIeqJeq> RackPinConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<RackPinConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIeqJeq::initialize()
{
    RackPinConstraintIeqJe::initialize();
    pGpXJ = FullRow<double>::With(3);
    pGpEJ = FullRow<double>::With(4);
    ppGpEIpXJ = FullMatrix<double>::With(4, 3);
    ppGpEIpEJ = FullMatrix<double>::With(4, 4);
    ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

void RackPinConstraintIeqJeq::initxIeJeIe()
{
    xIeJeIe = DispCompiIeJeIe::With(eFrmI, eFrmJ, 0);
    xIeJeIe->owner = this;
}

void RackPinConstraintIeqJeq::initthezIeJe()
{
    thezIeJe = AngleZIeqJeq::With(eFrmI, eFrmJ);
    thezIeJe->owner = this;
}

void RackPinConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = xIeJeIe->pvaluepEJ()->plusFullRow(thezIeJe->pvaluepEJ()->times(pitchRadius));
}

void RackPinConstraintIeqJeq::calcpGpXJ()
{
    pGpXJ = xIeJeIe->pvaluepXJ();
}

void RackPinConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = xIeJeIe->ppvaluepEIpEJ()
            ->plusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitchRadius));
}

void RackPinConstraintIeqJeq::calcppGpEIpXJ()
{
    ppGpEIpXJ = xIeJeIe->ppvaluepEIpXJ();
}

void RackPinConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = xIeJeIe->ppvaluepEJpEJ()
            ->plusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitchRadius));
}

void RackPinConstraintIeqJeq::simUpdateAll()
{
    RackPinConstraintIeqJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpEJpEJ();
}

void RackPinConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    RackPinConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto eFrmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = eFrmIeq->qEdot();
    auto qXdotJ = eFrmJeq->qXdot();
    auto qEdotJ = eFrmJeq->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(eFrmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(eFrmJeq->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void RackPinConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    RackPinConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void RackPinConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    RackPinConstraintIeqJe::fillPosICJacob(mat);
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

void RackPinConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    RackPinConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void RackPinConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    RackPinConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void RackPinConstraintIeqJeq::useEquationNumbers()
{
    RackPinConstraintIeqJe::useEquationNumbers();
    auto eFrmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqXJ = eFrmJeq->iqX();
    iqEJ = eFrmJeq->iqE();
}

void RackPinConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    RackPinConstraintIeqJe::fillpFpy(mat);
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

void RackPinConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    RackPinConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
