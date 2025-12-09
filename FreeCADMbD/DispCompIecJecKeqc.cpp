/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecKeqc> DispCompIecJecKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    auto inst = std::make_shared<DispCompIecJecKeqc>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIecJecKeqc::initialize()
{
    priIeJeKepEK = FullRow<double>::With(4);
    ppriIeJeKepEKpEK = FullMatrix<double>::With(4, 4);
}

void DispCompIecJecKeqc::initializeGlobally()
{
    ppAjOKepEKpEK = std::static_pointer_cast<EndFrameqc>(efrmK)->ppAjOepEpE(axisK);
}

void DispCompIecJecKeqc::calcPostDynCorrectorIteration()
{
    auto frmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto frmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
    aAjOKe = efrmKqc->aAjOe(axisK);
    rIeJeO = frmJqc->rOeO->minusFullColumn(frmIqc->rOeO);
    riIeJeKe = aAjOKe->dot(rIeJeO);
    pAjOKepEKT = efrmKqc->pAjOepET(axisK);
    ppAjOKepEKpEK = efrmKqc->ppAjOepEpE(axisK);
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeKepEK->at(i) = ((pAjOKepEKT->at(i))->dot(rIeJeO));
        auto& ppAjOKepEKipEK = ppAjOKepEKpEK->at(i);
        auto& ppriIeJeKepEKipEK = ppriIeJeKepEKpEK->at(i);
        ppriIeJeKepEKipEK->at(i) = ((ppAjOKepEKipEK->at(i))->dot(rIeJeO));
        for (size_t j = i + 1; j < 4; j++)
        {
            auto ppriIeJeKepEKipEKj = (ppAjOKepEKipEK->at(i))->dot(rIeJeO);
            ppriIeJeKepEKipEK->at(j) = ppriIeJeKepEKipEKj;
            ppriIeJeKepEKpEK->at(j)->at(i) = ppriIeJeKepEKipEKj;
        }
    }
}

FMatDsptr DispCompIecJecKeqc::ppvaluepEKpEK()
{
    return ppriIeJeKepEKpEK;
}

FRowDsptr DispCompIecJecKeqc::pvaluepEK()
{
    return priIeJeKepEK;
}
