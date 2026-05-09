/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZIeJeq.h"
#include "DirectionCosineIeJeq.h"

using namespace MbD;

std::shared_ptr<AngleZIeJeq> AngleZIeJeq::With()
{
    auto inst = std::make_shared<AngleZIeJeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AngleZIeJeq> AngleZIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<AngleZIeJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZIeJeq::initialize()
{
    AngleZIeJe::initialize();
    pthezpEJ = FullRow<double>::With(4);
    ppthezpEJpEJ = FullMatrix<double>::With(4, 4);
}

void AngleZIeJeq::simUpdateAll()
{
    //thezIeJe = atan2(sthez, cthez)
    //thezIeJe = atan2(aA10IeJe, aA00IeJe)
    AngleZIeJe::simUpdateAll();
    auto pcthezpEJ = aA00IeJe->pvaluepEJ();
    auto psthezpEJ = aA10IeJe->pvaluepEJ();
    auto ppcthezpEJpEJ = aA00IeJe->ppvaluepEJpEJ();
    auto ppsthezpEJpEJ = aA10IeJe->ppvaluepEJpEJ();
    for (size_t i = 0; i < 4; i++)
    {
        pthezpEJ->atiput(i, (psthezpEJ->at(i)) * cosOverSSq - ((pcthezpEJ->at(i)) * sinOverSSq));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto ppthezpEJpEJi = ppthezpEJpEJ->at(i);
        auto ppcthezpEJpEJi = ppcthezpEJpEJ->at(i);
        auto ppsthezpEJpEJi = ppsthezpEJpEJ->at(i);
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

void AngleZIeJeq::init_aAijIeJe()
{
    aA00IeJe = DirectionCosineIeJeq::With(eFrmI, eFrmJ, 0, 0);
    aA00IeJe->owner = this;
    aA10IeJe = DirectionCosineIeJeq::With(eFrmI, eFrmJ, 1, 0);
    aA10IeJe->owner = this;
}

FMatDsptr AngleZIeJeq::ppvaluepEJpEJ()
{
    return ppthezpEJpEJ;
}

FRowDsptr AngleZIeJeq::pvaluepEJ()
{
    return pthezpEJ;
}
