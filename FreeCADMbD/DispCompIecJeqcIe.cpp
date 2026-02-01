/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJeqcIe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJeqcIe> DispCompIecJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIecJeqcIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIecJeqcIe::initialize()
{
    DispCompIecJecIe::initialize();
    priIeJeIepXJ = FullRow<double>::With(3);
    priIeJeIepEJ = FullRow<double>::With(4);
    ppriIeJeIepXJpEJ = FullMatrix<double>::With(3, 4);
    ppriIeJeIepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DispCompIecJeqcIe::calc_ppvaluepEJpEJ()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto mprIeJeOpEJT = frmIeqc->prOeOpE->transpose();
    auto mpprIeJeOpEJpEJ = frmIeqc->pprOeOpEpE;
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAjOIepEJipEJ = ppAjOIepEJpEJ->at(i);
        auto mpprIeJeOpEJipEJ = mpprIeJeOpEJpEJ->at(i);
        auto ppriIeJeIepEJipEJ = ppriIeJeIepEJpEJ->at(i);
        for (size_t j = i; j < 4; j++)
        {
            auto term1 = ppAjOIepEJipEJ->at(j)->dot(rIeJeO);
            auto mterm2 = pAjOIepEJT->at(i)->dot(mprIeJeOpEJT->at(j));
            auto mterm3 = (i == j) ? mterm2 : pAjOIepEJT->at(j)->dot(mprIeJeOpEJT->at(i));
            auto mterm4 = aAjOIe->dot(mpprIeJeOpEJipEJ->at(j));
            ppriIeJeIepEJipEJ->atiput(j, term1 - mterm2 - mterm3 - mterm4);
        }
    }
    ppriIeJeIepEJpEJ->symLowerWithUpper();
}

void DispCompIecJeqcIe::calc_ppvaluepXJpEJ()
{
    for (size_t i = 0; i < 3; i++)
    {
        auto ppriIeJeIepXJipEJ = ppriIeJeIepXJpEJ->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppriIeJeIepXJipEJ->atiput(j, -pAjOIepEJT->at(j)->at(i));
        }
    }
}

void DispCompIecJeqcIe::calc_pvaluepEJ()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    pAjOIepEJT = frmIeqc->pAjOepET(axis);
    auto mprIeJeOpEJT = frmIeqc->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeIepEJ->atiput(i, pAjOIepEJT->at(i)->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpEJT->at(i)));
    }
}

void DispCompIecJeqcIe::calc_pvaluepXJ()
{
    for (size_t i = 0; i < 3; i++)
    {
        priIeJeIepXJ->atiput(i, -aAjOIe->at(i));
    }
}

void DispCompIecJeqcIe::calcPostDynCorrectorIteration()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeIe = aAIeO * rIeJeO
    //riIeJeIe = aArowiIeO dot rIeJeO = aAcoljOIe dot rIeJeO
    //Must maintain order of calc_xxx.
    DispCompIecJecIe::calcPostDynCorrectorIteration();
    calc_pvaluepXJ();
    calc_pvaluepEJ();
    calc_ppvaluepXJpEJ();
    calc_ppvaluepEJpEJ();
}

void DispCompIecJeqcIe::initializeGlobally()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    ppAjOIepEJpEJ = frmIeqc->ppAjOepEpE(axis);
}

FMatDsptr DispCompIecJeqcIe::ppvaluepEJpEJ()
{
    return ppriIeJeIepEJpEJ;
}

FMatDsptr DispCompIecJeqcIe::ppvaluepXJpEJ()
{
    return ppriIeJeIepXJpEJ;
}

FRowDsptr DispCompIecJeqcIe::pvaluepEJ()
{
    return priIeJeIepEJ;
}

FRowDsptr DispCompIecJeqcIe::pvaluepXJ()
{
    return priIeJeIepXJ;
}
