/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AngleZIeqJe.h"

using namespace MbD;

std::shared_ptr<AngleZIeqJe> AngleZIeqJe::With()
{
    auto inst = std::make_shared<AngleZIeqJe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AngleZIeqJe> AngleZIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<AngleZIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZIeqJe::initialize()
{
    AngleZIeJe::initialize();
    pthezpEI = FullRow<double>::With(4);
    ppthezpEIpEI = FullMatrix<double>::With(4, 4);
}

void AngleZIeqJe::simUpdateAll()
{
    //thezIeJe = atan2(sthez, cthez)
    //thezIeJe = atan2(aA10IeJe, aA00IeJe)
    AngleZIeJe::simUpdateAll();
    pcthezpEI = aA00IeJe->pvaluepEI();
    psthezpEI = aA10IeJe->pvaluepEI();
    auto ppcthezpEIpEI = aA00IeJe->ppvaluepEIpEI();
    auto ppsthezpEIpEI = aA10IeJe->ppvaluepEIpEI();
    for (size_t i = 0; i < 4; i++)
    {
        pthezpEI->atiput(i, (psthezpEI->at(i)) * cosOverSSq - ((pcthezpEI->at(i)) * sinOverSSq));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto ppthezpEIpEIi = ppthezpEIpEI->at(i);
        auto ppcthezpEIpEIi = ppcthezpEIpEI->at(i);
        auto ppsthezpEIpEIi = ppsthezpEIpEI->at(i);
        auto pcthezpEIi = pcthezpEI->at(i);
        auto psthezpEIi = psthezpEI->at(i);
        auto term1 = (pcthezpEIi * pcthezpEIi - (psthezpEIi * psthezpEIi)) * twoCosSinOverSSqSq;
        auto term2 = ppsthezpEIpEIi->at(i) * cosOverSSq - (ppcthezpEIpEIi->at(i) * sinOverSSq);
        auto term3 = (psthezpEIi * pcthezpEIi + (pcthezpEIi * psthezpEIi)) * dSqOverSSqSq;
        ppthezpEIpEIi->atiput(i, term1 + term2 + term3);
        for (size_t j = i + 1; j < 4; j++)
        {
            auto pcthezpEIj = pcthezpEI->at(j);
            auto psthezpEIj = psthezpEI->at(j);
            auto term1 = (pcthezpEIi * pcthezpEIj - (psthezpEIi * psthezpEIj)) * twoCosSinOverSSqSq;
            auto term2 = ppsthezpEIpEIi->at(j) * cosOverSSq - (ppcthezpEIpEIi->at(j) * sinOverSSq);
            auto term3 = (psthezpEIi * pcthezpEIj + (pcthezpEIi * psthezpEIj)) * dSqOverSSqSq;
            auto ppthezpEIpEIij = term1 + term2 + term3;
            ppthezpEIpEIi->atiput(j, ppthezpEIpEIij);
            ppthezpEIpEI->atijput(j, i, ppthezpEIpEIij);
        }
    }
}

void AngleZIeqJe::init_aAijIeJe()
{
    aA00IeJe = DirectionCosineIeqJe::With(eFrmI, eFrmJ, 0, 0);
    aA10IeJe = DirectionCosineIeqJe::With(eFrmI, eFrmJ, 1, 0);
}

FMatDsptr AngleZIeqJe::ppvaluepEIpEI()
{
    return ppthezpEIpEI;
}

FRowDsptr AngleZIeqJe::pvaluepEI()
{
    return pthezpEI;
}
