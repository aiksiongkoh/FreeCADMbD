/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeqJe.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeqJe> AtPointConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeqJe>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeqJe::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
}

void AtPointConstraintIeqJe::calcpGpXI()
{
    //pGpXI = [-I];
    auto prIeJeOpXI = dispIeJeO->getprIeJeOpXI();
    pGpXI = prIeJeOpXI->at(axis);
}

void AtPointConstraintIeqJe::calcpGpEI()
{
    auto prIeJeOpEI = dispIeJeO->getprIeJeOpEI();
    pGpEI = prIeJeOpEI->at(axis);
}

void AtPointConstraintIeqJe::calcppGpEIpEI()
{
    //ppGpEIpEI is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEIpEI = dispIeJeO->getppriIeJeOpEIpEI(axis);
}

void AtPointConstraintIeqJe::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeqJe::useEquationNumbers()
{
    AtPointConstraintIeJe::useEquationNumbers();
    iqXI = frmIe->iqX();
    iqEI = frmIe->iqE();
}

void AtPointConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
}

void AtPointConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
}

void AtPointConstraintIeqJe::fillPosICError(FColDsptr col)
{
    AtPointConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void AtPointConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());

    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AtPointConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
}

void AtPointConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
}
