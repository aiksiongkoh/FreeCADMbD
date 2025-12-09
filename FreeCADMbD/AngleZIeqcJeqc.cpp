/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AngleZIeqcJec.h"
#include "AngleZIeqcJeqc.h"
#include "DirectionCosineIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<AngleZIeqcJeqc> AngleZIeqcJeqc::With()
{
    auto inst = std::make_shared<AngleZIeqcJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AngleZIeqcJeqc> AngleZIeqcJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<AngleZIeqcJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZIeqcJeqc::initialize()
{
    AngleZIeqcJec::initialize();
    pthezpEJ = FullRow<double>::With(4);
    ppthezpEIpEJ = FullMatrix<double>::With(4, 4);
    ppthezpEJpEJ = FullMatrix<double>::With(4, 4);
}

void AngleZIeqcJeqc::calcPostDynCorrectorIteration()
{
    AngleZIeqcJec::calcPostDynCorrectorIteration();
    auto pcthezpEJ = aA00IeJe->pvaluepEJ();
    auto psthezpEJ = aA10IeJe->pvaluepEJ();
    auto ppcthezpEIpEJ = aA00IeJe->ppvaluepEIpEJ();
    auto ppsthezpEIpEJ = aA10IeJe->ppvaluepEIpEJ();
    auto ppcthezpEJpEJ = aA00IeJe->ppvaluepEJpEJ();
    auto ppsthezpEJpEJ = aA10IeJe->ppvaluepEJpEJ();
    for (size_t i = 0; i < 4; i++)
    {
        pthezpEJ->atiput(i, (psthezpEJ->at(i)) * cosOverSSq - ((pcthezpEJ->at(i)) * sinOverSSq));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppthezpEIpEJi = ppthezpEIpEJ->at(i);
        auto& ppcthezpEIpEJi = ppcthezpEIpEJ->at(i);
        auto& ppsthezpEIpEJi = ppsthezpEIpEJ->at(i);
        auto pcthezpEIi = pcthezpEI->at(i);
        auto psthezpEIi = psthezpEI->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pcthezpEJj = pcthezpEJ->at(j);
            auto psthezpEJj = psthezpEJ->at(j);
            auto term1 = (pcthezpEIi * pcthezpEJj - (psthezpEIi * psthezpEJj)) * twoCosSinOverSSqSq;
            auto term2 = ppsthezpEIpEJi->at(j) * cosOverSSq - (ppcthezpEIpEJi->at(j) * sinOverSSq);
            auto term3 = (psthezpEIi * pcthezpEJj + (pcthezpEIi * psthezpEJj)) * dSqOverSSqSq;
            ppthezpEIpEJi->atiput(j, term1 + term2 + term3);
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppthezpEJpEJi = ppthezpEJpEJ->at(i);
        auto& ppcthezpEJpEJi = ppcthezpEJpEJ->at(i);
        auto& ppsthezpEJpEJi = ppsthezpEJpEJ->at(i);
        auto pcthezpEJi = pcthezpEJ->at(i);
        auto psthezpEJi = psthezpEJ->at(i);
        auto term1 = (pcthezpEJi * pcthezpEJi - (psthezpEJi * psthezpEJi)) * twoCosSinOverSSqSq;
        auto term2 = ppsthezpEJpEJi->at(i) * cosOverSSq - (ppcthezpEJpEJi->at(i) * sinOverSSq);
        auto term3 = (psthezpEJi * pcthezpEJi + (pcthezpEJi * psthezpEJi)) * dSqOverSSqSq;
        ppthezpEJpEJi->atiput(i, term1 + term2 + term3);
        for (size_t j = i + 1; j < 4; j++)
        {
            auto pcthezpEJj = pcthezpEJ->at(j);
            auto psthezpEJj = psthezpEJ->at(j);
            auto term1 = (pcthezpEJi * pcthezpEJj - (psthezpEJi * psthezpEJj)) * twoCosSinOverSSqSq;
            auto term2 = ppsthezpEJpEJi->at(j) * cosOverSSq - (ppcthezpEJpEJi->at(j) * sinOverSSq);
            auto term3 = (psthezpEJi * pcthezpEJj + (pcthezpEJi * psthezpEJj)) * dSqOverSSqSq;
            auto ppthezpEJpEJij = term1 + term2 + term3;
            ppthezpEJpEJi->atiput(j, ppthezpEJpEJij);
            ppthezpEJpEJ->atijput(j, i, ppthezpEJpEJij);
        }
    }
}

void AngleZIeqcJeqc::init_aAijIeJe()
{
    aA00IeJe = DirectionCosineIeqcJeqc::With(eFrmI, eFrmJ, 0, 0);
    aA10IeJe = DirectionCosineIeqcJeqc::With(eFrmI, eFrmJ, 1, 0);
}

FMatDsptr AngleZIeqcJeqc::ppvaluepEIpEJ()
{
    return ppthezpEIpEJ;
}

FMatDsptr AngleZIeqcJeqc::ppvaluepEJpEJ()
{
    return ppthezpEJpEJ;
}

FRowDsptr AngleZIeqcJeqc::pvaluepEJ()
{
    return pthezpEJ;
}
