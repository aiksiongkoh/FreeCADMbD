/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJeqcKeqc> DispCompIeqcJeqcKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    auto inst = std::make_shared<DispCompIeqcJeqcKeqc>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIeqcJeqcKeqc::initialize()
{
    DispCompIeqcJecKeqc::initialize();
    priIeJeKepXJ = FullRow<double>::With(3);
    priIeJeKepEJ = FullRow<double>::With(4);
    ppriIeJeKepEJpEJ = FullMatrix<double>::With(4, 4);
    ppriIeJeKepXJpEK = FullMatrix<double>::With(3, 4);
    ppriIeJeKepEJpEK = FullMatrix<double>::With(4, 4);
}

void DispCompIeqcJeqcKeqc::calcPostDynCorrectorIteration()
{
    DispCompIeqcJecKeqc::calcPostDynCorrectorIteration();
    auto frmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto prIeJeOpEJT = frmJqc->prOeOpE->transpose();
    auto& pprIeJeOpEJpEJ = frmJqc->pprOeOpEpE;
    for (size_t i = 0; i < 3; i++)
    {
        priIeJeKepXJ->atiput(i, aAjOKe->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeKepEJ->atiput(i, aAjOKe->dot(prIeJeOpEJT->at(i)));
    }
    for (size_t i = 0; i < 3; i++)
    {
        auto& ppriIeJeKepXJipEK = ppriIeJeKepXJpEK->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppriIeJeKepXJipEK->atiput(j, pAjOKepEKT->at(j)->at(i));
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& pprIeJeOpEJipEJ = pprIeJeOpEJpEJ->at(i);
        auto& ppriIeJeKepEJipEJ = ppriIeJeKepEJpEJ->at(i);
        ppriIeJeKepEJipEJ->atiput(i, aAjOKe->dot(pprIeJeOpEJipEJ->at(i)));
        for (size_t j = 0; j < 4; j++)
        {
            auto ppriIeJeKepEJipEJj = (aAjOKe->dot(pprIeJeOpEJipEJ->at(j)));
            ppriIeJeKepEJipEJ->atiput(j, ppriIeJeKepEJipEJj);
            ppriIeJeKepEJpEJ->atijput(j, i, ppriIeJeKepEJipEJj);
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& prIeJeOpEJTi = prIeJeOpEJT->at(i);
        auto& ppriIeJeKepEJipEK = ppriIeJeKepEJpEK->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppriIeJeKepEJipEK->atiput(j, pAjOKepEKT->at(j)->dot(prIeJeOpEJTi));
        }
    }
}

FRowDsptr DispCompIeqcJeqcKeqc::pvaluepXJ()
{
    return priIeJeKepXJ;
}

FRowDsptr DispCompIeqcJeqcKeqc::pvaluepEJ()
{
    return priIeJeKepEJ;
}

FMatDsptr DispCompIeqcJeqcKeqc::ppvaluepXJpEK()
{
    return ppriIeJeKepXJpEK;
}

FMatDsptr DispCompIeqcJeqcKeqc::ppvaluepEJpEK()
{
    return ppriIeJeKepEJpEK;
}

FMatDsptr DispCompIeqcJeqcKeqc::ppvaluepEJpEJ()
{
    return ppriIeJeKepEJpEJ;
}
