/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeqJe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeqJe> AtPointConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeqJe>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeqJe::simUpdateAll()
{
    AtPointConstraintIeJe::simUpdateAll();
    // calcpGpXI(); //Constant
    calcpGpEI();
    // calcppGpEIpEI(); //Constant
}

void AtPointConstraintIeqJe::initializeGlobally()
{
    AtPointConstraintIeJe::initializeGlobally();
    calcpGpXI(); //Constant
    calcppGpEIpEI(); //Constant
}

void AtPointConstraintIeqJe::calcpGpXI()
{
    //pGpXI = [-I];
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    pGpXI = prIeJeOpXI->at(axis);
}

void AtPointConstraintIeqJe::calcpGpEI()
{
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    pGpEI = prIeJeOpEI->at(axis);
}

void AtPointConstraintIeqJe::calcppGpEIpEI()
{
    //ppGpEIpEI is constant for EndFrameq, but not for EndFrameqt.
    ppGpEIpEI = dispIeJeO->getppCompipEIpEI(axis);
}

void AtPointConstraintIeqJe::initializeLocally()
{
    AtPointConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeqJe::useEquationNumbers()
{
    AtPointConstraintIeJe::useEquationNumbers();
    iqXI = eFrmI->iqX();
    iqEI = eFrmI->iqE();
}

void AtPointConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AtPointConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
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
    AtPointConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullColumn(iqXI, iG, pGpXI->transpose());
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AtPointConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    AtPointConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqXI, pGpXI);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void AtPointConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqXI, pGpXI, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qXdotI = eFrmIeq->qXdot();
    auto qEdotI = eFrmIeq->qEdot();
    auto sum = pGpXI->timesFullColumn(eFrmIeq->qXddot());
    sum += pGpEI->timesFullColumn(eFrmIeq->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void AtPointConstraintIeqJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //auto aFIeO = pGpXI->transpose()->times(lam);
    //col->equalSelfPlus(aFIeO);
    col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void AtPointConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    auto aFIeOT = pGpXI->times(lam);
    auto rIpIeIp = eFrmI->rpep();
    auto pAOIppEI = eFrmI->pAOppE();
    auto aBOIp = eFrmI->aBOp();
    auto prOIeOpEITaFIeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOIeOpEIT * aFIeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOIeOpEIi = pAOIppEI->at(i)->timesFullColumn(rIpIeIp);
        auto prOIeOpEITaFIeOi = aFIeOT->timesFullColumn(prOIeOpEIi);
        prOIeOpEITaFIeO->atiput(i, prOIeOpEITaFIeOi);
    }
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI->minusFullColumn(prOIeOpEITaFIeO))->times(0.5);
    col->equalSelfPlus(aTIeO);
}
