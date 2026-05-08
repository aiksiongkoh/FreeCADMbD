/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIeqJeq.h"
#include "EndFrameq.h"
#include "OrbitAngleZIeqJeq.h"

using namespace MbD;

std::shared_ptr<GearConstraintIeqJeq> GearConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<GearConstraintIeqJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void GearConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = orbitJeIe->pvaluepEI()->plusFullRow(orbitIeJe->pvaluepEJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcpGpXJ()
{
    pGpXJ = orbitJeIe->pvaluepXI()->plusFullRow(orbitIeJe->pvaluepXJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = orbitJeIe->ppvaluepEIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpEJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpEIpXJ()
{
    ppGpEIpXJ = orbitJeIe->ppvaluepXIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpXJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = orbitJeIe->ppvaluepEIpEI()->plusFullMatrix(orbitIeJe->ppvaluepEJpEJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpXIpEJ()
{
    ppGpXIpEJ = orbitJeIe->ppvaluepEIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpEJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpXIpXJ()
{
    ppGpXIpXJ = orbitJeIe->ppvaluepXIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpXJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpXJpEJ()
{
    ppGpXJpEJ = orbitJeIe->ppvaluepXIpEI()->plusFullMatrix(orbitIeJe->ppvaluepXJpEJ()->times(ratio()));
}

void GearConstraintIeqJeq::calcppGpXJpXJ()
{
    ppGpXJpXJ = orbitJeIe->ppvaluepXIpXI()->plusFullMatrix(orbitIeJe->ppvaluepXJpXJ()->times(ratio()));
}

void GearConstraintIeqJeq::simUpdateAll()
{
    GearConstraintIeqJe::simUpdateAll();
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

void GearConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    GearConstraintIeqJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    double sum = 0.0;
    sum += pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += qXdotJ->transposeTimesFullColumn(ppGpXJpXJ->timesFullColumn(qXdotJ));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += 2.0 * (qXdotJ->transposeTimesFullColumn(ppGpXJpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void GearConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    GearConstraintIeqJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void GearConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    GearConstraintIeqJe::fillPosICJacob(mat);
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

void GearConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    GearConstraintIeqJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void GearConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    GearConstraintIeqJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void GearConstraintIeqJeq::initorbitsIJ()
{
    orbitIeJe = OrbitAngleZIeqJeq::With(eFrmI, eFrmJ);
    orbitIeJe->owner = this;
    orbitJeIe = OrbitAngleZIeqJeq::With(eFrmJ, eFrmI);
    orbitJeIe->owner = this;
}

void GearConstraintIeqJeq::useEquationNumbers()
{
    GearConstraintIeqJe::useEquationNumbers();
    auto frmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    iqXJ = frmJeq->iqX();
    iqEJ = frmJeq->iqE();
}

void GearConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    GearConstraintIeqJe::fillpFpy(mat);
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

void GearConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    GearConstraintIeqJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
