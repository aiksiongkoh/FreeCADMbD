/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIcJqc.h"
#include "DirectionCosineIecJeqc.h"
#include "EndFrameqc.h"
#include "FullColumn.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIcJqc> DirectionCosineConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIcJqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIcJqc::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIecJeqc::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIcJqc::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //frmIec does not have q, we use frmJeqc
    //aFJeO = lam * pGpXJ = zero
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ)
    //aTIeO = rJeIeO cross aFJeO - aTJeO
    //aTIeO = -aTJeO

    auto aBOJp = eFrmJ->aBOp();
    auto lampGpEJ = pGpEJ->transpose()->times(lam);  //lam * pGpEJ
    auto aTJeO = aBOJp->timesFullColumn(lampGpEJ)->times(0.5);
    auto aTIeO = aTJeO->negated();
    col->equalSelfPlus(aTIeO);
}

void DirectionCosineConstraintIcJqc::calcPostDynCorrectorIteration()
{
    //aG = aAijIeJe - aConstant;
    DirectionCosineConstraintIJ::calcPostDynCorrectorIteration();
    auto aAijIeqJqe = std::static_pointer_cast<DirectionCosineIecJeqc>(aAijIeJe);
    pGpEJ = aAijIeqJqe->pAijIeJepEJ;
    ppGpEJpEJ = aAijIeqJqe->ppAijIeJepEJpEJ;
}

void DirectionCosineConstraintIcJqc::useEquationNumbers()
{
    DirectionCosineConstraintIJ::useEquationNumbers();
    iqEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->iqE();
}

void DirectionCosineConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
    DirectionCosineConstraintIJ::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
    DirectionCosineConstraintIJ::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

FRowDsptr DirectionCosineConstraintIcJqc::pGpEI()
{
    auto aAjOJe = eFrmJ->aAjOe(axisJ);
    auto pAjOIepEIT = eFrmI->pAjOepET(axisI);
    auto pAijIeJepEI = FullRow<double>::With(4);
    for (size_t i = 0; i < 4; i++)
    {
        pAijIeJepEI->at(i) = pAjOIepEIT->at(i)->dot(aAjOJe);
    }
    return pAijIeJepEI;
}

void DirectionCosineConstraintIcJqc::fillPosICError(FColDsptr col)
{
    DirectionCosineConstraintIJ::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIJ::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIJ::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
    DirectionCosineConstraintIJ::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIJ::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
