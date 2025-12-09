/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJecIe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJecIe> DispCompIeqcJecIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIeqcJecIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIeqcJecIe::initialize()
{
    DispCompIecJecIe::initialize();
    priIeJeIepXI = FullRow<double>::With(3);
    priIeJeIepEI = FullRow<double>::With(4);
    ppriIeJeIepXIpEI = FullMatrix<double>::With(3, 4);
    ppriIeJeIepEIpEI = FullMatrix<double>::With(4, 4);
}

void DispCompIeqcJecIe::calc_ppvaluepEIpEI()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto mprIeJeOpEIT = frmIeqc->prOeOpE->transpose();
    auto mpprIeJeOpEIpEI = frmIeqc->pprOeOpEpE;
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAjOIepEIipEI = ppAjOIepEIpEI->at(i);
        auto mpprIeJeOpEIipEI = mpprIeJeOpEIpEI->at(i);
        auto ppriIeJeIepEIipEI = ppriIeJeIepEIpEI->at(i);
        for (size_t j = i; j < 4; j++)
        {
            auto term1 = ppAjOIepEIipEI->at(j)->dot(rIeJeO);
            auto mterm2 = pAjOIepEIT->at(i)->dot(mprIeJeOpEIT->at(j));
            auto mterm3 = (i == j) ? mterm2 : pAjOIepEIT->at(j)->dot(mprIeJeOpEIT->at(i));
            auto mterm4 = aAjOIe->dot(mpprIeJeOpEIipEI->at(j));
            ppriIeJeIepEIipEI->atiput(j, term1 - mterm2 - mterm3 - mterm4);
        }
    }
    ppriIeJeIepEIpEI->symLowerWithUpper();
}

void DispCompIeqcJecIe::calc_ppvaluepXIpEI()
{
    for (size_t i = 0; i < 3; i++)
    {
        auto ppriIeJeIepXIipEI = ppriIeJeIepXIpEI->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppriIeJeIepXIipEI->atiput(j, -pAjOIepEIT->at(j)->at(i));
        }
    }
}

void DispCompIeqcJecIe::calc_pvaluepEI()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    pAjOIepEIT = frmIeqc->pAjOepET(axis);
    auto mprIeJeOpEIT = frmIeqc->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeIepEI->atiput(i, pAjOIepEIT->at(i)->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpEIT->at(i)));
    }
}

void DispCompIeqcJecIe::calc_pvaluepXI()
{
    for (size_t i = 0; i < 3; i++)
    {
        priIeJeIepXI->atiput(i, -aAjOIe->at(i));
    }
}

void DispCompIeqcJecIe::calcPostDynCorrectorIteration()
{
    //Must maintain order of calc_xxx.
    DispCompIecJecIe::calcPostDynCorrectorIteration();
    calc_pvaluepXI();
    calc_pvaluepEI();
    calc_ppvaluepXIpEI();
    calc_ppvaluepEIpEI();
}

void DispCompIeqcJecIe::initializeGlobally()
{
    auto frmIeqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    ppAjOIepEIpEI = frmIeqc->ppAjOepEpE(axis);
}

FMatDsptr DispCompIeqcJecIe::ppvaluepEIpEI()
{
    return ppriIeJeIepEIpEI;
}

FMatDsptr DispCompIeqcJecIe::ppvaluepXIpEI()
{
    return ppriIeJeIepXIpEI;
}

FRowDsptr DispCompIeqcJecIe::pvaluepEI()
{
    return priIeJeIepEI;
}

FRowDsptr DispCompIeqcJecIe::pvaluepXI()
{
    return priIeJeIepXI;
}
