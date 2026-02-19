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

void AtPointConstraintIeqJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
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
    ConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
}

void AtPointConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
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
    ConstraintIeJe::fillVelICJacob(mat);
}

void AtPointConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
}
