/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AngleZIecJeqc.h"
#include "DirectionCosineIecJeqc.h"

using namespace MbD;

std::shared_ptr<AngleZIecJeqc> AngleZIecJeqc::With()
{
    auto inst = std::make_shared<AngleZIecJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AngleZIecJeqc> AngleZIecJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<AngleZIecJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void AngleZIecJeqc::initialize()
{
    AngleZIecJec::initialize();
    pthezpEJ = FullRow<double>::With(4);
    ppthezpEJpEJ = FullMatrix<double>::With(4, 4);
}

void AngleZIecJeqc::calcPostDynCorrectorIteration()
{
    //thezIeJe = atan2(sthez, cthez)
    //thezIeJe = atan2(aA10IeJe, aA00IeJe)
    AngleZIecJec::calcPostDynCorrectorIteration();
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

void AngleZIecJeqc::init_aAijIeJe()
{
    aA00IeJe = DirectionCosineIecJeqc::With(eFrmI, eFrmJ, 0, 0);
    aA10IeJe = DirectionCosineIecJeqc::With(eFrmI, eFrmJ, 1, 0);
}

FMatDsptr AngleZIecJeqc::ppvaluepEJpEJ()
{
    return ppthezpEJpEJ;
}

FRowDsptr AngleZIecJeqc::pvaluepEJ()
{
    return pthezpEJ;
}
