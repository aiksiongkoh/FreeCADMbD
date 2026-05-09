/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <cmath>
#include <numbers>

#include "ScrewConstraintIeqJe.h"
#include "EndFrameq.h"
#include "DispCompiIeJeIe.h"
#include "AngleZIeqJe.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIeqJe> ScrewConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ScrewConstraintIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ScrewConstraintIeqJe::initialize()
{
    ScrewConstraintIeJe::initialize();
    pGpXI = FullRow<double>::With(3);
    pGpEI = FullRow<double>::With(4);
    ppGpXIpEI = FullMatrix<double>::With(3, 4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void ScrewConstraintIeqJe::initthezIeJe()
{
    thezIeJe = AngleZIeqJe::With(eFrmI, eFrmJ);
}

void ScrewConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void ScrewConstraintIeqJe::addToJointTorqueI(FColDsptr col)
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

void ScrewConstraintIeqJe::calcpGpEI()
{
    pGpEI = zIeJeIe->pvaluepEI()->times(2.0 * std::numbers::pi)->minusFullRow(thezIeJe->pvaluepEI()->times(pitch));
}

void ScrewConstraintIeqJe::calcpGpXI()
{
    pGpXI = zIeJeIe->pvaluepXI()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIeqJe::calcppGpEIpEI()
{
    ppGpEIpEI = zIeJeIe->ppvaluepEIpEI()->times(2.0 * std::numbers::pi)
        ->minusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitch));
}

void ScrewConstraintIeqJe::calcppGpXIpEI()
{
    ppGpXIpEI = zIeJeIe->ppvaluepXIpEI()->times(2.0 * std::numbers::pi);
}

void ScrewConstraintIeqJe::simUpdateAll()
{
    ScrewConstraintIeJe::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpEI();
    calcppGpEIpEI();
}

void ScrewConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void ScrewConstraintIeqJe::fillPosICError(FColDsptr col)
{
    ScrewConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void ScrewConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ScrewConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void ScrewConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void ScrewConstraintIeqJe::useEquationNumbers()
{
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    iqXI = frmIeq->iqX();
    iqEI = frmIeq->iqE();
}

void ScrewConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ScrewConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string ScrewConstraintIeqJe::constraintSpec()
{
    return "ScrewConstraintIeJe";
}
