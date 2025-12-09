/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZConstraintIqcJqc.h"
#include "AngleZIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

void AngleZConstraintIqcJqc::initthezIeJe()
{
    thezIeJe = std::make_shared<AngleZIeqcJeqc>(eFrmI, eFrmJ);
}

void AngleZConstraintIqcJqc::calc_pGpEJ()
{
    pGpEJ = thezIeJe->pvaluepEJ();
}

void AngleZConstraintIqcJqc::calc_ppGpEIpEJ()
{
    ppGpEIpEJ = thezIeJe->ppvaluepEIpEJ();
}

void AngleZConstraintIqcJqc::calc_ppGpEJpEJ()
{
    ppGpEJpEJ = thezIeJe->ppvaluepEJpEJ();
}

void AngleZConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    AngleZConstraintIqcJc::calcPostDynCorrectorIteration();
    this->calc_pGpEJ();
    this->calc_ppGpEIpEJ();
    this->calc_ppGpEJpEJ();
}

void AngleZConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    AngleZConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = frmIeqc->qEdot();
    auto qXdotJ = frmJeqc->qXdot();
    auto qEdotJ = frmJeqc->qEdot();
    double sum = 0.0;
    sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void AngleZConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    AngleZConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AngleZConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    AngleZConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AngleZConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    AngleZConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AngleZConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    AngleZConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AngleZConstraintIqcJqc::useEquationNumbers()
{
    AngleZConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqEJ = frmJeqc->iqE();
}
