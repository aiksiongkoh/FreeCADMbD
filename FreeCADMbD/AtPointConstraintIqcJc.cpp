/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIqcJc.h"
#include "DispCompIeqcJecO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIqcJc> AtPointConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIqcJc>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIqcJc::initializeGlobally()
{
    AtPointConstraintIJ::initializeGlobally();
    ppGpEIpEI = (std::static_pointer_cast<DispCompIeqcJecO>(riIeJeO))->ppriIeJeOpEIpEI;
}

void AtPointConstraintIqcJc::initriIeJeO()
{
    riIeJeO = DispCompIeqcJecO::With(eFrmI, eFrmJ, axis);
}

void AtPointConstraintIqcJc::simUpdateAll()
{
    //riIeJeO = rOJeO - rOIeO;
    //aG = riIeJeO - C;
    AtPointConstraintIJ::simUpdateAll();
    pGpEI = std::static_pointer_cast<DispCompIeqcJecO>(riIeJeO)->priIeJeOpEI;
}

void AtPointConstraintIqcJc::useEquationNumbers()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    iqXIminusOnePlusAxis = frmIeqc->iqX() + axis;
    iqEI = frmIeqc->iqE();
}

void AtPointConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AtPointConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string AtPointConstraintIqcJc::constraintSpec()
{
    return "AtPointConstraintIJ";
}

void AtPointConstraintIqcJc::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiminusNumber(iqXIminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void AtPointConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
    mat->atijplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AtPointConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void AtPointConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
    mat->atijplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AtPointConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiminusNumber(iqXIminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qEdotI = eFrmIqc->qEdot();
    auto sum = -eFrmIqc->qXddot()->at(axis);
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void AtPointConstraintIqcJc::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * priIeJeOpXI
    //aFIeO = lam * [-I]coli
    col->atiminusNumber(axis, lam);
}

void AtPointConstraintIqcJc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    auto aFIeOT = FullRow<double>::With(3, 0.0);
    aFIeOT->atiput(axis, -lam);
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
