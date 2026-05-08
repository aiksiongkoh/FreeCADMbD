/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIeqJe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DistIeqJe> DistIeqJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIeqJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIeqJe::initialize()
{
    DistIeJe::initialize();
    prIeJepXI = FullRow<double>::With(3);
    prIeJepEI = FullRow<double>::With(4);
    pprIeJepXIpXI = FullMatrix<double>::With(3, 3);
    pprIeJepXIpEI = FullMatrix<double>::With(3, 4);
    pprIeJepEIpEI = FullMatrix<double>::With(4, 4);
}

void DistIeqJe::calcPrivate()
{
    DistIeJe::calcPrivate();
    if (rIeJe == 0.0) return;
    auto mprIeJeOpEI = dispIeJeO->getpVectorpEI()->negated();
    mprIeJeOpEIT = mprIeJeOpEI->transpose();
    auto mpprIeJeOpEIpEI = dispIeJeO->getppVectorpEIpEI()->negated();
    auto muIeJeOT = muIeJeO->transpose();
    prIeJepXI = muIeJeOT;
    prIeJepEI = muIeJeOT->timesFullMatrix(mprIeJeOpEI);
    for (size_t i = 0; i < 3; i++)
    {
        auto pprIeJepXIipXI = pprIeJepXIpXI->at(i);
        auto prIeJepXIi = prIeJepXI->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto element = (i == j) ? 1.0 : 0.0;
            element -= prIeJepXIi * prIeJepXI->at(j);
            pprIeJepXIipXI->atiput(j, element / rIeJe);
        }
    }
    for (size_t i = 0; i < 3; i++)
    {
        auto pprIeJepXIipEI = pprIeJepXIpEI->at(i);
        auto prIeJepXIi = prIeJepXI->at(i);
        auto mprIeJeOipEI = mprIeJeOpEI->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto element = mprIeJeOipEI->at(j) - prIeJepXIi * prIeJepEI->at(j);
            pprIeJepXIipEI->atiput(j, element / rIeJe);
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto pprIeJepEIipEI = pprIeJepEIpEI->at(i);
        auto prIeJepEIi = prIeJepEI->at(i);
        auto mpprIeJeOpEIipEI = mpprIeJeOpEIpEI->at(i);
        auto mprIeJeOpEIiT = mprIeJeOpEIT->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto element = mprIeJeOpEIiT->dot(mprIeJeOpEIT->at(j))
                - mpprIeJeOpEIipEI->at(j)->dot(rIeJeO) - prIeJepEIi * prIeJepEI->at(j);
            pprIeJepEIipEI->atiput(j, element / rIeJe);
        }
    }
}

FMatDsptr DistIeqJe::ppvaluepEIpEI()
{
    return pprIeJepEIpEI;
}

FMatDsptr DistIeqJe::ppvaluepXIpEI()
{
    return pprIeJepXIpEI;
}

FMatDsptr DistIeqJe::ppvaluepXIpXI()
{
    return pprIeJepXIpXI;
}

FMatDsptr DistIeqJe::puIeJeOpEI()
{
    auto answer = FullMatrix<double>::With(3, 4);
    auto mprIeJeOpEI = dispIeJeO->getpVectorpEI()->negated();
    auto m1OverrIeJe = -1.0 / rIeJe;
    auto m1OverrIeJeSq = m1OverrIeJe / rIeJe;
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        auto mprIeJeOpEIi = mprIeJeOpEI->at(i);
        auto rIeJeOi = rIeJeO->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto aij = mprIeJeOpEIi->at(j) * m1OverrIeJe + (rIeJeOi * prIeJepEI->at(j) * m1OverrIeJeSq);
            answeri->atiput(j, aij);
        }
    }
    return answer;
}

FMatDsptr DistIeqJe::puIeJeOpXI()
{
    auto answer = FullMatrix<double>::With(3, 3);
    auto m1OverrIeJe = -1.0 / rIeJe;
    auto m1OverrIeJeSq = m1OverrIeJe / rIeJe;
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        auto rIeJeOi = rIeJeO->at(i);
        for (size_t j = 0; j < 3; j++) {
            auto aij = rIeJeOi * prIeJepXI->at(j) * m1OverrIeJeSq;
            answeri->atiput(j, aij);
        }
        answeri->atiplusNumber(i, m1OverrIeJe);
    }
    return answer;
}

FRowDsptr DistIeqJe::pvaluepEI()
{
    return prIeJepEI;
}

FRowDsptr DistIeqJe::pvaluepXI()
{
    return prIeJepXI;
}
