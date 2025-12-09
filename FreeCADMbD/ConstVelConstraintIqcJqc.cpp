/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstVelConstraintIqcJqc.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ConstVelConstraintIqcJqc> ConstVelConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ConstVelConstraintIqcJqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ConstVelConstraintIqcJqc::initialize()
{
    ConstVelConstraintIqcJc::initialize();
    pGpEJ = FullRow<double>::With(4);
    ppGpEIpEJ = FullMatrix<double>::With(4, 4);
    ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

void ConstVelConstraintIqcJqc::calcPostDynCorrectorIteration()
{
    ConstVelConstraintIqcJc::calcPostDynCorrectorIteration();
    auto aA01IeqcJeqc = std::dynamic_pointer_cast<DirectionCosineIeqcJeqc>(aA01IeJe);
    auto& pA01IeJepEJ = aA01IeqcJeqc->pAijIeJepEJ;
    auto& ppA01IeJepEIpEJ = aA01IeqcJeqc->ppAijIeJepEIpEJ;
    auto& ppA01IeJepEJpEJ = aA01IeqcJeqc->ppAijIeJepEJpEJ;
    auto aA10IeqcJeqc = std::dynamic_pointer_cast<DirectionCosineIeqcJeqc>(aA10IeJe);
    auto& pA10IeJepEJ = aA10IeqcJeqc->pAijIeJepEJ;
    auto& ppA10IeJepEIpEJ = aA10IeqcJeqc->ppAijIeJepEIpEJ;
    auto& ppA10IeJepEJpEJ = aA10IeqcJeqc->ppAijIeJepEJpEJ;
    for (size_t i = 0; i < 4; i++)
    {
        pGpEJ->atiput(i, pA01IeJepEJ->at(i) + pA10IeJepEJ->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppGpEIpEJi = ppGpEIpEJ->at(i);
        auto& ppA01IeJepEIpEJi = ppA01IeJepEIpEJ->at(i);
        auto& ppA10IeJepEIpEJi = ppA10IeJepEIpEJ->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto ppGpEIpEJij = ppA01IeJepEIpEJi->at(j) + ppA10IeJepEIpEJi->at(j);
            ppGpEIpEJi->atiput(j, ppGpEIpEJij);
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppGpEJpEJi = ppGpEJpEJ->at(i);
        auto& ppA01IeJepEJpEJi = ppA01IeJepEJpEJ->at(i);
        auto& ppA10IeJepEJpEJi = ppA10IeJepEJpEJ->at(i);
        ppGpEJpEJi->atiput(i, ppA01IeJepEJpEJi->at(i) + ppA10IeJepEJpEJi->at(i));
        for (size_t j = i + 1; j < 4; j++)
        {
            auto ppGpEJpEJij = ppA01IeJepEJpEJi->at(j) + ppA10IeJepEJpEJi->at(j);
            ppGpEJpEJi->atiput(j, ppGpEJpEJij);
            ppGpEJpEJ->atijput(j, i, ppGpEJpEJij);
        }
    }

}

void ConstVelConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
    ConstVelConstraintIqcJc::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto qEdotI = eFrmIqc->qEdot();
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = 0.0;
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += 2.0 * qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ));
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void ConstVelConstraintIqcJqc::fillPosICError(FColDsptr col)
{
    ConstVelConstraintIqcJc::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void ConstVelConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
    ConstVelConstraintIqcJc::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void ConstVelConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
    ConstVelConstraintIqcJc::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void ConstVelConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
    ConstVelConstraintIqcJc::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void ConstVelConstraintIqcJqc::initA01IeJe()
{
    aA01IeJe = DirectionCosineIeqcJeqc::With(eFrmI, eFrmJ, 0, 1);
}

void ConstVelConstraintIqcJqc::initA10IeJe()
{
    aA10IeJe = DirectionCosineIeqcJeqc::With(eFrmI, eFrmJ, 1, 0);
}

void ConstVelConstraintIqcJqc::useEquationNumbers()
{
    ConstVelConstraintIqcJc::useEquationNumbers();
    iqEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->iqE();
}

void ConstVelConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
    ConstVelConstraintIqcJc::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void ConstVelConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
    ConstVelConstraintIqcJc::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

std::string ConstVelConstraintIqcJqc::constraintSpec()
{
    return "ConstVelConstraintIJ";
}
