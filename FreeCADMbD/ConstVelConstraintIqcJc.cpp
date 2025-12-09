/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "ConstVelConstraintIqcJc.h"
#include "DirectionCosineIeqcJec.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ConstVelConstraintIqcJc> ConstVelConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ConstVelConstraintIqcJc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ConstVelConstraintIqcJc::initialize()
{
    ConstVelConstraintIJ::initialize();
    pGpEI = FullRow<double>::With(4);
    ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void ConstVelConstraintIqcJc::calcPostDynCorrectorIteration()
{
    ConstVelConstraintIJ::calcPostDynCorrectorIteration();
    auto aA01IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqcJec>(aA01IeJe);
    auto& pA01IeJepEI = aA01IeqcJec->pAijIeJepEI;
    auto& ppA01IeJepEIpEI = aA01IeqcJec->ppAijIeJepEIpEI;
    auto aA10IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqcJec>(aA10IeJe);
    auto& pA10IeJepEI = aA10IeqcJec->pAijIeJepEI;
    auto& ppA10IeJepEIpEI = aA10IeqcJec->ppAijIeJepEIpEI;
    for (size_t i = 0; i < 4; i++)
    {
        pGpEI->atiput(i, pA01IeJepEI->at(i) + pA10IeJepEI->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppGpEIpEIi = ppGpEIpEI->at(i);
        auto& ppA01IeJepEIpEIi = ppA01IeJepEIpEI->at(i);
        auto& ppA10IeJepEIpEIi = ppA10IeJepEIpEI->at(i);
        ppGpEIpEIi->atiput(i, ppA01IeJepEIpEIi->at(i) + ppA10IeJepEIpEIi->at(i));
        for (size_t j = i + 1; j < 4; j++)
        {
            auto ppGpEIpEIij = ppA01IeJepEIpEIi->at(j) + ppA10IeJepEIpEIi->at(j);
            ppGpEIpEIi->atiput(j, ppGpEIpEIij);
            ppGpEIpEI->atijput(j, i, ppGpEIpEIij);
        }
    }
}

void ConstVelConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qEdotI = eFrmIqc->qEdot();
    double sum = 0.0;
    sum += pGpEI->timesFullColumn(eFrmIqc->qEddot());
    sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
    col->atiplusNumber(iG, sum);
}

void ConstVelConstraintIqcJc::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiplusFullVectortimes(iqEI, pGpEI, lam);
}

void ConstVelConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ConstVelConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
}

void ConstVelConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void ConstVelConstraintIqcJc::initA01IeJe()
{
    aA01IeJe = DirectionCosineIeqcJec::With(eFrmI, eFrmJ, 0, 1);
}

void ConstVelConstraintIqcJc::initA10IeJe()
{
    aA10IeJe = DirectionCosineIeqcJec::With(eFrmI, eFrmJ, 1, 0);
}

void ConstVelConstraintIqcJc::useEquationNumbers()
{
    iqEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->iqE();
}

void ConstVelConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqEI, pGpEI);
    mat->atijplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void ConstVelConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqEI, iG, pGpEI->transpose());
}

std::string ConstVelConstraintIqcJc::constraintSpec()
{
    return "ConstVelConstraintIJ";
}
