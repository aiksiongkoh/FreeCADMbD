/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIeJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DistIeJeq> DistIeJeq::With()
{
    auto inst = std::make_shared<DistIeJeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DistIeJeq> DistIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIeJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIeJeq::initialize()
{
    DistIeJe::initialize();
    prIeJepXJ = FullRow<double>::With(3);
    prIeJepEJ = FullRow<double>::With(4);
    pprIeJepXJpXJ = FullMatrix<double>::With(3, 3);
    pprIeJepXJpEJ = FullMatrix<double>::With(3, 4);
    pprIeJepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DistIeJeq::calcPrivate()
{
    DistIeJe::calcPrivate();
    if (rIeJe == 0.0) return;
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    auto prIeJeOpEJT = prIeJeOpEJ->transpose();
    auto pprIeJeOpEJpEJ = dispIeJeO->getppVectorpEJpEJ();
    auto uIeJeOT = uIeJeO->transpose();
    prIeJepXJ = uIeJeOT;
    prIeJepEJ = uIeJeOT->timesFullMatrix(prIeJeOpEJ);

    for (size_t i = 0; i < 3; i++)
    {
        auto pprIeJepXJipXJ = pprIeJepXJpXJ->at(i);
        auto prIeJepXJi = prIeJepXJ->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto element = (i == j) ? 1.0 : 0.0;
            element -= prIeJepXJi * prIeJepXJ->at(j);
            pprIeJepXJipXJ->atiput(j, element / rIeJe);
        }
    }

    for (size_t i = 0; i < 3; i++)
    {
        auto pprIeJepXJipEJ = pprIeJepXJpEJ->at(i);
        auto prIeJepXJi = prIeJepXJ->at(i);
        auto prIeJeOipEJ = prIeJeOpEJ->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto element = prIeJeOipEJ->at(j) - prIeJepXJi * prIeJepEJ->at(j);
            pprIeJepXJipEJ->atiput(j, element / rIeJe);
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        auto pprIeJepEJipEJ = pprIeJepEJpEJ->at(i);
        auto prIeJepEJi = prIeJepEJ->at(i);
        auto pprIeJeOpEJipEJ = pprIeJeOpEJpEJ->at(i);
        auto prIeJeOpEJiT = prIeJeOpEJT->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto element = prIeJeOpEJiT->dot(prIeJeOpEJT->at(j))
                + pprIeJeOpEJipEJ->at(j)->dot(rIeJeO) - prIeJepEJi * prIeJepEJ->at(j);
            pprIeJepEJipEJ->atiput(j, element / rIeJe);
        }
    }
}

FMatDsptr DistIeJeq::ppvaluepEJpEJ()
{
    return pprIeJepEJpEJ;
}

FMatDsptr DistIeJeq::ppvaluepXJpEJ()
{
    return pprIeJepXJpEJ;
}

FMatDsptr DistIeJeq::ppvaluepXJpXJ()
{
    return pprIeJepXJpXJ;
}

FMatDsptr DistIeJeq::puIeJeOpEJ()
{
    auto answer = FullMatrix<double>::With(3, 4);
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    auto oneOverrIeJe = 1.0 / rIeJe;
    auto oneOverrIeJeSq = oneOverrIeJe / rIeJe;
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        auto prIeJeOpEJi = prIeJeOpEJ->at(i);
        auto rIeJeOi = rIeJeO->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto aij = prIeJeOpEJi->at(j) * oneOverrIeJe - (rIeJeOi * prIeJepEJ->at(j) * oneOverrIeJeSq);
            answeri->atiput(j, aij);
        }
    }
    return answer;
}

FMatDsptr DistIeJeq::puIeJeOpXJ()
{
    auto answer = FullMatrix<double>::With(3, 3);
    auto m1OverrIeJe = -1.0 / rIeJe;
    auto m1OverrIeJeSq = m1OverrIeJe / rIeJe;
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        auto rIeJeOi = rIeJeO->at(i);
        for (size_t j = 0; j < 3; j++) {
            auto aij = rIeJeOi * prIeJepXJ->at(j) * m1OverrIeJeSq;
            answeri->atiput(j, aij);
        }
        answeri->atiminusNumber(i, m1OverrIeJe);
    }
    return answer;
}

FRowDsptr DistIeJeq::pvaluepEJ()
{
    return prIeJepEJ;
}

FRowDsptr DistIeJeq::pvaluepXJ()
{
    return prIeJepXJ;
}
