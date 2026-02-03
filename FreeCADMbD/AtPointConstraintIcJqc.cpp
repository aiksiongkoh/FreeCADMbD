/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIcJqc.h"
#include "DispCompIecJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIcJqc> AtPointConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIcJqc>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIcJqc::initializeGlobally()
{
    AtPointConstraintIJ::initializeGlobally();
    ppGpEJpEJ = (std::static_pointer_cast<DispCompIecJeqcO>(riIeJeO))->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIcJqc::initriIeJeO()
{
    riIeJeO = DispCompIecJeqcO::With(eFrmI, eFrmJ, axis);
}

void AtPointConstraintIcJqc::simUpdateAll()
{
    //riIeJeO = rOJeO - rOIeO;
    //aG = riIeJeO - C;
    AtPointConstraintIJ::simUpdateAll();
    pGpEJ = std::static_pointer_cast<DispCompIecJeqcO>(riIeJeO)->priIeJeOpEJ;
}

void AtPointConstraintIcJqc::useEquationNumbers()
{
    AtPointConstraintIJ::useEquationNumbers();
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    iqXJminusOnePlusAxis = frmJeqc->iqX() + axis;
    iqEJ = frmJeqc->iqE();
}

void AtPointConstraintIcJqc::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ
    //aFIeO = -aFJeO
    auto aFJeO = FullColumn<double>::With(3, 0.0);
    aFJeO->atiput(axis, lam);
    col->equalSelfMinus(aFJeO);
}

void AtPointConstraintIcJqc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - p(aAOJp * rJpJeJp)pEJT * aFJeO)
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - (pAOJppEJ * rJpJeJp)T * aFJeO)
    //aTJeO = rIeJeO cross aFIeO - aTIeO
    //aTIeO = rJeIeO cross aFJeO - aTJeO

    auto aFJeOT = FullRow<double>::With(3, 0.0);
    aFJeOT->atiput(axis, lam);
    auto rJpJeJp = eFrmJ->rpep();
    auto pAOJppEJ = eFrmJ->pAOppE();
    auto aBOJp = eFrmJ->aBOp();
    auto prOJeOpEJTaFJeO = std::make_shared<FullColumn<double>>(4, 0.0);    //prOJeOpEJT * aFJeO
    for (size_t i = 0; i < 4; i++)
    {
        auto prOJeOpEJTaFJeOi = aFJeOT->timesFullColumn(pAOJppEJ->at(i)->timesFullColumn(rJpJeJp));
        prOJeOpEJTaFJeO->atiput(i, prOJeOpEJTaFJeOi);
    }
    auto lampGpEJ = pGpEJ->transpose()->times(lam);  //lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ->minusFullColumn(prOJeOpEJTaFJeO))->times(0.5);
    auto rJeIeO = getrIeJeO()->negated();
    auto aFJeO = aFJeOT->transpose();
    auto aTIeO = rJeIeO->cross(aFJeO)->minusFullColumn(aTJeO);
    col->equalSelfPlus(aTIeO);
}

void AtPointConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
    AtPointConstraintIJ::fillpFpy(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
    AtPointConstraintIJ::fillpFpydot(mat);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIcJqc::fillPosICError(FColDsptr col)
{
    AtPointConstraintIJ::fillPosICError(col);
    col->atiplusNumber(iqXJminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
    AtPointConstraintIJ::fillPosICJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    AtPointConstraintIJ::fillPosKineJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void AtPointConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
    AtPointConstraintIJ::fillVelICJacob(mat);
    mat->atijplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
    mat->atijplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIJ::fillAccICIterError(col);
    col->atiplusNumber(iqXJminusOnePlusAxis, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotJ = eFrmJqc->qEdot();
    auto sum = eFrmJqc->qXddot()->at(axis);
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
