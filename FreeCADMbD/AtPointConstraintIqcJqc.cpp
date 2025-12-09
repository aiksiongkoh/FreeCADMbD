/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIqcJqc.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIqcJqc> AtPointConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIqcJqc>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIqcJqc::initializeGlobally()
{
    AtPointConstraintIqcJc::initializeGlobally();
    ppGpEJpEJ = (std::static_pointer_cast<DispCompIeqcJeqcO>(riIeJeO))->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIqcJqc::initriIeJeO()
{
    riIeJeO = DispCompIeqcJeqcO::With(eFrmI, eFrmJ, axis);
}

void AtPointConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    AtPointConstraintIqcJc::calcPostDynCorrectorIteration();
    pGpEJ = std::static_pointer_cast<DispCompIeqcJeqcO>(riIeJeO)->priIeJeOpEJ;
}

void AtPointConstraintIqcJqc::useEquationNumbers()
{
    AtPointConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJminusOnePlusAxis = frmJeqc->iqX() + axis;
    iqEJ = frmJeqc->iqE();
}

void AtPointConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    AtPointConstraintIqcJc::fillpFpy(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    AtPointConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

std::string AtPointConstraintIqcJqc::constraintSpec()
{
    return "AtPointConstraintIJ";
}

void AtPointConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    AtPointConstraintIqcJc::fillPosICError(col);
    col->atiplusNumber(iqXJminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    AtPointConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    AtPointConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AtPointConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    AtPointConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIqcJc::fillAccICIterError(col);
    col->atiplusNumber(iqXJminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotJ = eFrmJqc->qEdot();
    auto sum = eFrmJqc->qXddot()->at(axis);
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
