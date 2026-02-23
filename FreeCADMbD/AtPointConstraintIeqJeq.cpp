/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIeqJeq.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeqJeq> AtPointConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeqJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeqJeq::simUpdateAll()
{
    AtPointConstraintIeqJe::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpEJpEJ();
}

void AtPointConstraintIeqJeq::initializeGlobally()
{
    AtPointConstraintIeqJe::initializeGlobally();
}

void AtPointConstraintIeqJeq::calcpGpXJ()
{
    //pGpXJ = [I];
    auto prIeJeOpXJ = dispIeJeO->getprIeJeOpXJ();
    pGpXJ = prIeJeOpXJ->at(axis);
}

void AtPointConstraintIeqJeq::calcpGpEJ()
{
    auto prIeJeOpEJ = dispIeJeO->getprIeJeOpEJ();
    pGpEJ = prIeJeOpEJ->at(axis);
}

void AtPointConstraintIeqJeq::calcppGpEJpEJ()
{
    //ppGpEJpEJ is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEJpEJ = dispIeJeO->getppriIeJeOpEJpEJ(axis);
}

void AtPointConstraintIeqJeq::useEquationNumbers()
{
    AtPointConstraintIeqJe::useEquationNumbers();
    iqXJ = frmJe->iqX();
    iqEJ = frmJe->iqE();
}

void AtPointConstraintIeqJeq::initializeLocally()
{
    AtPointConstraintIeqJe::initializeLocally();
}

void AtPointConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    AtPointConstraintIeqJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    AtPointConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    AtPointConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    AtPointConstraintIeqJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    AtPointConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
