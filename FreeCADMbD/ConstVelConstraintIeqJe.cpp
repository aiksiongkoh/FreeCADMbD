/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "ConstVelConstraintIeqJe.h"
#include "DirectionCosineIeqJe.h"
#include "DirectionCosineIeqJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<ConstVelConstraintIeqJe> ConstVelConstraintIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ConstVelConstraintIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ConstVelConstraintIeqJe::initialize()
{
    ConstVelConstraintIeJe::initialize();
    pGpEI = FullRow<double>::With(4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void ConstVelConstraintIeqJe::simUpdateAll()
{
    //aG = aA01IeJe + aA10IeJe - aConstant;
    ConstVelConstraintIeJe::simUpdateAll();
    auto aA01IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqJe>(aA01IeJe);
    auto pA01IeJepEI = aA01IeqcJec->pAijIeJepEI;
    auto ppA01IeJepEIpEI = aA01IeqcJec->ppAijIeJepEIpEI;
    auto aA10IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqJe>(aA10IeJe);
    auto pA10IeJepEI = aA10IeqcJec->pAijIeJepEI;
    auto ppA10IeJepEIpEI = aA10IeqcJec->ppAijIeJepEIpEI;
    for (size_t i = 0; i < 4; i++)
    {
        pGpEI->atiput(i, pA01IeJepEI->at(i) + pA10IeJepEI->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto ppGpEIpEIi = ppGpEIpEI->at(i);
        auto ppA01IeJepEIpEIi = ppA01IeJepEIpEI->at(i);
        auto ppA10IeJepEIpEIi = ppA10IeJepEIpEI->at(i);
        ppGpEIpEIi->atiput(i, ppA01IeJepEIpEIi->at(i) + ppA10IeJepEIpEIi->at(i));
        for (size_t j = i + 1; j < 4; j++)
        {
            auto ppGpEIpEIij = ppA01IeJepEIpEIi->at(j) + ppA10IeJepEIpEIi->at(j);
            ppGpEIpEIi->atiput(j, ppGpEIpEIij);
            ppGpEIpEI->atijput(j, i, ppGpEIpEIij);
        }
    }
}

void ConstVelConstraintIeqJe::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qEdotI = eFrmIeq->qEdot();
    double sum = 0.0;
    sum += pGpEI->timesFullColumn(eFrmIeq->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void ConstVelConstraintIeqJe::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void ConstVelConstraintIeqJe::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ConstVelConstraintIeqJe::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void ConstVelConstraintIeqJe::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void ConstVelConstraintIeqJe::initA01IeJe()
{
    aA01IeJe = DirectionCosineIeqJe::With(eFrmI, eFrmJ, 0, 1);
}

void ConstVelConstraintIeqJe::initA10IeJe()
{
    aA10IeJe = DirectionCosineIeqJe::With(eFrmI, eFrmJ, 1, 0);
}

void ConstVelConstraintIeqJe::useEquationNumbers()
{
    iqEI = std::static_pointer_cast<EndFrameq>(eFrmI)->iqE();
}

void ConstVelConstraintIeqJe::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ConstVelConstraintIeqJe::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string ConstVelConstraintIeqJe::constraintSpec()
{
    return "ConstVelConstraintIeJe";
}

void ConstVelConstraintIeqJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //aFIeO = zero;
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI)
    auto aBOIp = eFrmI->aBOp();
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI)->times(0.5);
    col->equalSelfPlus(aTIeO);
}
