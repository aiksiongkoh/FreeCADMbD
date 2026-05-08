/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIqcJc.h"
#include "EndFrameq.h"
//#include "EndFrame.h"
#include "DispCompiIeJeIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIqcJc> DistancexyConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistancexyConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistancexyConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void DistancexyConstraintIqcJc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    auto aFIeOT = pGpXI->times(lam);
    auto rIpIeIp = eFrmI->rpep();
    auto pAOIppEI = eFrmI->pAOppE();
    auto aBOIp = eFrmI->aBOp();
    auto prOIeOpEITaFIeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOIeOpEIT * aFIeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOIeOpEITaFIeOi = aFIeOT->timesFullColumn(pAOIppEI->at(i)->timesFullColumn(rIpIeIp));
        prOIeOpEITaFIeO->atiput(i, prOIeOpEITaFIeOi);
    }
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI->minusFullColumn(prOIeOpEITaFIeO))->times(0.5);
    col->equalSelfPlus(aTIeO);
}

void DistancexyConstraintIqcJc::simUpdateAll()
{
    //aG = xIeJeIe^2 + yIeJeIe^2 - C^2;
    DistancexyConstraintIJ::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpXI();
    calcppGpXIpEI();
    calcppGpEIpEI();
}

void DistancexyConstraintIqcJc::calcpGpEI()
{
    pGpEI = (xIeJeIe->pvaluepEI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEI()->times(yIeJeIe->value())));
    pGpEI->magnifySelf(2.0);
}

void DistancexyConstraintIqcJc::calcpGpXI()
{
    pGpXI = (xIeJeIe->pvaluepXI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXI()->times(yIeJeIe->value())));
    pGpXI->magnifySelf(2.0);
}

void DistancexyConstraintIqcJc::calcppGpEIpEI()
{
    ppGpEIpEI = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(xIeJeIe->ppvaluepEIpEI()->times(xIeJeIe->value()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
    ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->ppvaluepEIpEI()->times(yIeJeIe->value()));
    ppGpEIpEI->magnifySelf(2.0);
}

void DistancexyConstraintIqcJc::calcppGpXIpEI()
{
    ppGpXIpEI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(xIeJeIe->ppvaluepXIpEI()->times(xIeJeIe->value()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
    ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->ppvaluepXIpEI()->times(yIeJeIe->value()));
    ppGpXIpEI->magnifySelf(2.0);
}

void DistancexyConstraintIqcJc::calcppGpXIpXI()
{
    //xIeJeIe ppvaluepXIpXI = 0
    //yIeJeIe ppvaluepXIpXI = 0
    ppGpXIpXI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXI()));
    ppGpXIpXI = ppGpXIpXI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXI()));
    ppGpXIpXI->magnifySelf(2.0);
}

void DistancexyConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void DistancexyConstraintIqcJc::fillPosICError(FColDsptr col)
{
    DistancexyConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void DistancexyConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistancexyConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void DistancexyConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DistancexyConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void DistancexyConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DistancexyConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string DistancexyConstraintIqcJc::constraintSpec()
{
    return "DistancexyConstraintIJ";
}


