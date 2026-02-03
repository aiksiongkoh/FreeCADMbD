/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJeqcKec.h"
#include "EndFramec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJeqcKec> DispCompIecJeqcKec::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    assert(!frmi->has_qX());
    assert(frmj->has_qX());
    assert(!frmk->has_qX());
    auto inst = std::make_shared<DispCompIecJeqcKec>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIecJeqcKec::initialize()
{
    DispCompIecJecKec::initialize();
    priIeJeKepXJ = FullRow<double>::With(3);
    priIeJeKepEJ = FullRow<double>::With(4);
    ppriIeJeKepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DispCompIecJeqcKec::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //riIeJeKe = aArowiKeO dot rIeJeO = aAcoljOKe dot rIeJeO
    auto frmIec = std::static_pointer_cast<EndFramec>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto efrmKc = std::static_pointer_cast<EndFramec>(efrmK);
    aAjOKe = efrmKc->aAjOe(axisK);
    rIeJeO = frmJeqc->rOeO->minusFullColumn(frmIec->rOeO);
    riIeJeKe = aAjOKe->dot(rIeJeO);
    auto prIeJeOpEJT = frmJeqc->prOeOpE->transpose();
    auto pprIeJeOpEJpEJ = frmJeqc->pprOeOpEpE;
    for (size_t i = 0; i < 3; i++)
    {
        priIeJeKepXJ->atiput(i, aAjOKe->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeKepEJ->atiput(i, aAjOKe->dot(prIeJeOpEJT->at(i)));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto pprIeJeOpEJipEJ = pprIeJeOpEJpEJ->at(i);
        auto ppriIeJeKepEJipEJ = ppriIeJeKepEJpEJ->at(i);
        ppriIeJeKepEJipEJ->atiput(i, aAjOKe->dot(pprIeJeOpEJipEJ->at(i)));
        for (size_t j = 0; j < 4; j++)
        {
            auto ppriIeJeKepEJipEJj = (aAjOKe->dot(pprIeJeOpEJipEJ->at(j)));
            ppriIeJeKepEJipEJ->atiput(j, ppriIeJeKepEJipEJj);
            ppriIeJeKepEJpEJ->atijput(j, i, ppriIeJeKepEJipEJj);
        }
    }
}

FRowDsptr DispCompIecJeqcKec::pvaluepXJ()
{
    return priIeJeKepXJ;
}

FRowDsptr DispCompIecJeqcKec::pvaluepEJ()
{
    return priIeJeKepEJ;
}

FMatDsptr DispCompIecJeqcKec::ppvaluepEJpEJ()
{
    return ppriIeJeKepEJpEJ;
}
