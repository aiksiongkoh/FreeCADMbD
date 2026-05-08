/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIeqJeq.h"
#include "AngleZIeqJeq.h"
#include "EndFrameq.h"

using namespace MbD;

void AngleZConstraintIeqJeq::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqJeq>(eFrmI, eFrmJ);
}

void AngleZConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = thezIeJe->pvaluepEJ();
}

void AngleZConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = thezIeJe->ppvaluepEIpEJ();
}

void AngleZConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = thezIeJe->ppvaluepEJpEJ();
}

void AngleZConstraintIeqJeq::simUpdateAll()
{
    //aG = thezIeJe - C
    AngleZConstraintIeqJe::simUpdateAll();
    calcpGpEJ();
    calcppGpEIpEJ();
    calcppGpEJpEJ();
}

void AngleZConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    AngleZConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    AngleZConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AngleZConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    AngleZConstraintIeqJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AngleZConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    AngleZConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AngleZConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    AngleZConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AngleZConstraintIeqJeq::useEquationNumbers()
{
    AngleZConstraintIeqJe::useEquationNumbers();
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqEJ = frmJeq->iqE();
}
