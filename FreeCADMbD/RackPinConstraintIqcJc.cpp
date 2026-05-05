/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "AngleZIeqcJec.h"
#include "DispCompiIeJeIe.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIqcJc> RackPinConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<RackPinConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void RackPinConstraintIqcJc::initialize()
{
    RackPinConstraintIJ::initialize();
    pGpXI = FullRow<double>::With(3);
    pGpEI = FullRow<double>::With(4);
    ppGpXIpEI = FullMatrix<double>::With(3, 4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void RackPinConstraintIqcJc::initthezIeJe()
{
    thezIeJe = AngleZIeqcJec::With(eFrmI, eFrmJ);
}

void RackPinConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void RackPinConstraintIqcJc::addToJointTorqueI(FColDsptr col)
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

void RackPinConstraintIqcJc::calcpGpEI()
{
    pGpEI = xIeJeIe->pvaluepEI()->plusFullRow(thezIeJe->pvaluepEI()->times(pitchRadius));
}

void RackPinConstraintIqcJc::calcpGpXI()
{
    pGpXI = xIeJeIe->pvaluepXI();
}

void RackPinConstraintIqcJc::calcppGpEIpEI()
{
    ppGpEIpEI = xIeJeIe->ppvaluepEIpEI()
            ->plusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitchRadius));
}

void RackPinConstraintIqcJc::calcppGpXIpEI()
{
    ppGpXIpEI = xIeJeIe->ppvaluepXIpEI();
}

void RackPinConstraintIqcJc::simUpdateAll()
{
    RackPinConstraintIJ::simUpdateAll();
    calcpGpXI();
    calcpGpEI();
    calcppGpXIpEI();
    calcppGpEIpEI();
}

void RackPinConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qXdotI = eFrmIqc->qXdot();
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIqc->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void RackPinConstraintIqcJc::fillPosICError(FColDsptr col)
{
    RackPinConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void RackPinConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void RackPinConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void RackPinConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void RackPinConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXI = frmIeqc->iqX();
    iqEI = frmIeqc->iqE();
}

void RackPinConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
    mat->atijplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
    mat->atijplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void RackPinConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}
