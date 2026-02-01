/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIecJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DistIecJeqc> DistIecJeqc::With()
{
    auto inst = std::make_shared<DistIecJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DistIecJeqc> DistIecJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIecJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIecJeqc::initialize()
{
    DistIecJec::initialize();
    prIeJepXJ = FullRow<double>::With(3);
    prIeJepEJ = FullRow<double>::With(4);
    pprIeJepXJpXJ = FullMatrix<double>::With(3, 3);
    pprIeJepXJpEJ = FullMatrix<double>::With(3, 4);
    pprIeJepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DistIecJeqc::calcPrivate()
{
    DistIecJec::calcPrivate();
    if (rIeJe == 0.0) return;
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto prIeJeOpEJ = frmJeqc->prOeOpE;
    auto prIeJeOpEJT = prIeJeOpEJ->transpose();
    auto pprIeJeOpEJpEJ = frmJeqc->pprOeOpEpE;
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

FMatDsptr DistIecJeqc::ppvaluepEJpEJ()
{
    return pprIeJepEJpEJ;
}

FMatDsptr DistIecJeqc::ppvaluepXJpEJ()
{
    return pprIeJepXJpEJ;
}

FMatDsptr DistIecJeqc::ppvaluepXJpXJ()
{
    return pprIeJepXJpXJ;
}

FMatDsptr DistIecJeqc::puIeJeOpEJ()
{
    auto answer = FullMatrix<double>::With(3, 4);
    auto prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE;
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

FMatDsptr DistIecJeqc::puIeJeOpXJ()
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

FRowDsptr DistIecJeqc::pvaluepEJ()
{
    return prIeJepEJ;
}

FRowDsptr DistIecJeqc::pvaluepXJ()
{
    return prIeJepXJ;
}
