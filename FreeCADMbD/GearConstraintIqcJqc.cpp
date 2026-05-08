/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIqcJqc.h"
#include "EndFrameq.h"
#include "OrbitAngleZIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<GearConstraintIqcJqc> GearConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<GearConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIqcJqc::calcpGpEJ()
{
    pGpEJ = orbitJeIe->pvaluepEI()->plusFullRow(orbitIeJe->pvaluepEJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcpGpXJ()
{
    pGpXJ = orbitJeIe->pvaluepXI()->plusFullRow(orbitIeJe->pvaluepXJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpEIpEJ()
{
    ppGpEIpEJ = orbitJeIe->ppvaluepEIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpEJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpEIpXJ()
{
    ppGpEIpXJ = orbitJeIe->ppvaluepXIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpXJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpEJpEJ()
{
    ppGpEJpEJ = orbitJeIe->ppvaluepEIpEI()->plusFullMatrix(orbitIeJe->ppvaluepEJpEJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpXIpEJ()
{
    ppGpXIpEJ = orbitJeIe->ppvaluepEIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpEJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpXIpXJ()
{
    ppGpXIpXJ = orbitJeIe->ppvaluepXIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpXJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpXJpEJ()
{
    ppGpXJpEJ = orbitJeIe->ppvaluepXIpEI()->plusFullMatrix(orbitIeJe->ppvaluepXJpEJ()->times(ratio()));
}

void GearConstraintIqcJqc::calcppGpXJpXJ()
{
    ppGpXJpXJ = orbitJeIe->ppvaluepXIpXI()->plusFullMatrix(orbitIeJe->ppvaluepXJpXJ()->times(ratio()));
}

void GearConstraintIqcJqc::simUpdateAll()
{
    GearConstraintIqcJc::simUpdateAll();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpXIpXJ();
    calcppGpXIpEJ();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpXJpXJ();
    calcppGpXJpEJ();
    calcppGpEJpEJ();
}

void GearConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    GearConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameq>(eFrmJ);
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

void GearConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    GearConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void GearConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    GearConstraintIqcJc::fillPosICJacob(mat);
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

void GearConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    GearConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void GearConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    GearConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void GearConstraintIqcJqc::initorbitsIJ()
{
    orbitIeJe = OrbitAngleZIeqcJeqc::With(eFrmI, eFrmJ);
    orbitIeJe->owner = this;
    orbitJeIe = OrbitAngleZIeqcJeqc::With(eFrmJ, eFrmI);
    orbitJeIe->owner = this;
}

void GearConstraintIqcJqc::useEquationNumbers()
{
    GearConstraintIqcJc::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqXJ = frmJeqc->iqX();
    iqEJ = frmJeqc->iqE();
}

void GearConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    GearConstraintIqcJc::fillpFpy(mat);
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

void GearConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    GearConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
