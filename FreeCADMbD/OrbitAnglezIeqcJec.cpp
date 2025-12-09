/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "OrbitAngleZIeqcJec.h"
#include "DispCompIeqcJecIe.h"

using namespace MbD;

std::shared_ptr<OrbitAngleZIeqcJec> OrbitAngleZIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OrbitAngleZIeqcJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OrbitAngleZIeqcJec::initialize()
{
    OrbitAngleZIecJec::initialize();
    pthezpXI = FullRow<double>::With(3);
    pthezpEI = FullRow<double>::With(4);
    ppthezpXIpXI = FullMatrix<double>::With(3, 3);
    ppthezpXIpEI = FullMatrix<double>::With(3, 4);
    ppthezpEIpEI = FullMatrix<double>::With(4, 4);
}

void OrbitAngleZIeqcJec::calc_ppthezpEIpEI()
{
    auto pxpEI = xIeJeIe->pvaluepEI();
    auto pypEI = yIeJeIe->pvaluepEI();
    auto ppxpEIpEI = xIeJeIe->ppvaluepEIpEI();
    auto ppypEIpEI = yIeJeIe->ppvaluepEIpEI();
    for (size_t i = 0; i < 4; i++)
    {
        auto ppthezpEIpEIi = ppthezpEIpEI->at(i);
        auto ppxpEIpEIi = ppxpEIpEI->at(i);
        auto ppypEIpEIi = ppypEIpEI->at(i);
        auto pxpEIi = pxpEI->at(i);
        auto pypEIi = pypEI->at(i);
        for (size_t j = i; j < 4; j++)
        {
            auto pxpEIj = pxpEI->at(j);
            auto pypEIj = pypEI->at(j);
            auto term1 = (pxpEIi * pxpEIj - (pypEIi * pypEIj)) * twoCosSinOverSSqSq;
            auto term2 = ppypEIpEIi->at(j) * cosOverSSq - (ppxpEIpEIi->at(j) * sinOverSSq);
            auto term3 = (pypEIi * pxpEIj + (pxpEIi * pypEIj)) * dSqOverSSqSq;
            auto ppthezpEIpEIij = term1 + term2 + term3;
            ppthezpEIpEIi->atiput(j, ppthezpEIpEIij);
            if (i < j) ppthezpEIpEI->atijput(j, i, ppthezpEIpEIij);
        }
    }
}

void OrbitAngleZIeqcJec::calc_ppthezpXIpEI()
{
    auto pxpXI = xIeJeIe->pvaluepXI();
    auto pypXI = yIeJeIe->pvaluepXI();
    auto pxpEI = xIeJeIe->pvaluepEI();
    auto pypEI = yIeJeIe->pvaluepEI();
    auto ppxpXIpEI = xIeJeIe->ppvaluepXIpEI();
    auto ppypXIpEI = yIeJeIe->ppvaluepXIpEI();
    for (size_t i = 0; i < 3; i++)
    {
        auto ppthezpXIpEIi = ppthezpXIpEI->at(i);
        auto ppxpXIpEIi = ppxpXIpEI->at(i);
        auto ppypXIpEIi = ppypXIpEI->at(i);
        auto pxpXIi = pxpXI->at(i);
        auto pypXIi = pypXI->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pxpEIj = pxpEI->at(j);
            auto pypEIj = pypEI->at(j);
            auto term1 = (pxpXIi * pxpEIj - (pypXIi * pypEIj)) * twoCosSinOverSSqSq;
            auto term2 = ppypXIpEIi->at(j) * cosOverSSq - (ppxpXIpEIi->at(j) * sinOverSSq);
            auto term3 = (pypXIi * pxpEIj + (pxpXIi * pypEIj)) * dSqOverSSqSq;
            ppthezpXIpEIi->atiput(j, term1 + term2 + term3);
        }
    }
}

void OrbitAngleZIeqcJec::calc_ppthezpXIpXI()
{
    //ppxpXIpXI = 0
    //ppypXIpXI = 0

    auto pxpXI = xIeJeIe->pvaluepXI();
    auto pypXI = yIeJeIe->pvaluepXI();
    for (size_t i = 0; i < 3; i++)
    {
        auto ppthezpXIpXIi = ppthezpXIpXI->at(i);
        auto pxpXIi = pxpXI->at(i);
        auto pypXIi = pypXI->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto pxpXIj = pxpXI->at(j);
            auto pypXIj = pypXI->at(j);
            auto term1 = (pxpXIi * pxpXIj - (pypXIi * pypXIj)) * twoCosSinOverSSqSq;
            auto term3 = (pypXIi * pxpXIj + (pxpXIi * pypXIj)) * dSqOverSSqSq;
            ppthezpXIpXIi->atiput(j, term1 + term3);
        }
    }
}

void OrbitAngleZIeqcJec::calc_pthezpEI()
{
    auto pxpEI = xIeJeIe->pvaluepEI();
    auto pypEI = yIeJeIe->pvaluepEI();
    for (size_t i = 0; i < 4; i++)
    {
        pthezpEI->atiput(i, pypEI->at(i) * cosOverSSq - (pxpEI->at(i) * sinOverSSq));
    }
}

void OrbitAngleZIeqcJec::calc_pthezpXI()
{
    auto pxpXI = xIeJeIe->pvaluepXI();
    auto pypXI = yIeJeIe->pvaluepXI();
    for (size_t i = 0; i < 3; i++)
    {
        pthezpXI->atiput(i, pypXI->at(i) * cosOverSSq - (pxpXI->at(i) * sinOverSSq));
    }
}

void OrbitAngleZIeqcJec::calcPostDynCorrectorIteration()
{
    OrbitAngleZIecJec::calcPostDynCorrectorIteration();
    calc_pthezpXI();
    calc_pthezpEI();
    calc_ppthezpXIpXI();
    calc_ppthezpXIpEI();
    calc_ppthezpEIpEI();
}

void OrbitAngleZIeqcJec::init_xyIeJeIe()
{
    xIeJeIe = DispCompIeqcJecIe::With(eFrmI, eFrmJ, 0);
    yIeJeIe = DispCompIeqcJecIe::With(eFrmI, eFrmJ, 1);
}

FMatDsptr OrbitAngleZIeqcJec::ppvaluepEIpEI()
{
    return ppthezpEIpEI;
}

FMatDsptr OrbitAngleZIeqcJec::ppvaluepXIpEI()
{
    return ppthezpXIpEI;
}

FMatDsptr OrbitAngleZIeqcJec::ppvaluepXIpXI()
{
    return ppthezpXIpXI;
}

FRowDsptr OrbitAngleZIeqcJec::pvaluepEI()
{
    return pthezpEI;
}

FRowDsptr OrbitAngleZIeqcJec::pvaluepXI()
{
    return pthezpXI;
}
