/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIeJe.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ConstraintIeJe> ConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIeJe>();
}

void ConstraintIeJe::initialize()
{
    Constraint::initialize();
    dispIeJeO = DispIecJecO::With(frmIe, frmJe);
    aConstant = 0.0;
}

void MbD::ConstraintIeJe::initializeLocally()
{
    dispIeJeO->initializeLocally();
}

void MbD::ConstraintIeJe::initializeGlobally()
{
    dispIeJeO->initializeGlobally();
}

void MbD::ConstraintIeJe::useEquationNumbers()
{
    iqXI = frmIe->iqX();
    iqEI = frmIe->iqE();
    iqXJ = frmJe->iqX();
    iqEJ = frmJe->iqE();
}

void MbD::ConstraintIeJe::prePosIC()
{
    dispIeJeO->prePosIC();
    lam = 0.0;
    iG = SIZE_MAX;
    Constraint::prePosIC();
}

void MbD::ConstraintIeJe::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::ConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
    auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);

    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
    mat->atijplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);

    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);

    mat->atijplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);

    mat->atijplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::ConstraintIeJe::postPosICIteration()
{
    dispIeJeO->postPosICIteration();
    Constraint::postPosICIteration();
}

void MbD::ConstraintIeJe::preVelIC()
{
    dispIeJeO->preVelIC();
    Constraint::preVelIC();
}

void MbD::ConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::ConstraintIeJe::preAccIC()
{
    dispIeJeO->preAccIC();
    Constraint::preAccIC();
}

void MbD::ConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    Constraint::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto frmIeq = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto frmJeq = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qXdotI = frmIeq->qXdot();
    auto qEdotI = frmIeq->qEdot();
    auto qXdotJ = frmJeq->qXdot();
    auto qEdotJ = frmJeq->qEdot();
    auto sum = 0.0;
    sum += pGpXI->timesFullColumn(frmIeq->qXddot());
    sum += pGpEI->timesFullColumn(frmIeq->qEddot());
    sum += pGpXJ->timesFullColumn(frmJeq->qXddot());
    sum += pGpEJ->timesFullColumn(frmJeq->qEddot());
    sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
    sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
    sum += qXdotJ->transposeTimesFullColumn(ppGpXJpXJ->timesFullColumn(qXdotJ));
    sum += 2.0 * (qXdotJ->transposeTimesFullColumn(ppGpXJpEJ->timesFullColumn(qEdotJ)));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void MbD::ConstraintIeJe::preDyn()
{
    dispIeJeO->preDyn();
    Constraint::preDyn();
}

void MbD::ConstraintIeJe::preDynOutput()
{
    dispIeJeO->preDynOutput();
    Constraint::preDynOutput();
}

void MbD::ConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);

    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
    auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
    auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);

    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
    mat->atijplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);

    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
    mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);

    mat->atijplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
    mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);

    mat->atijplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::ConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::ConstraintIeJe::postInput()
{
    dispIeJeO->postInput();
    lam = 0.0;
    Constraint::postInput();
}

void MbD::ConstraintIeJe::simUpdateAll()
{
    //Update locally only.
    calcG();
    calcpGpXI();
    calcpGpEI();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpXIpXI();
    calcppGpXIpEI();
    calcppGpXIpXJ();
    calcppGpXIpEJ();
    calcppGpEIpEI();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpXJpXJ();
    calcppGpXJpEJ();
    calcppGpEJpEJ();
}

std::string ConstraintIeJe::constraintSpec()
{
    return "ConstraintIeJe";
}

void ConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //aFJeO = lam * pGpXJ
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ConstraintIeJe::getrIeJeO()
{
    return frmJe->rOeO->minusFullColumn(frmIe->rOeO);
}
