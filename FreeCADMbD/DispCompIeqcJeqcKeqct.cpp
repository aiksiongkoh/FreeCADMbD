/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJeqcKeqct.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJeqcKeqct> DispCompIeqcJeqcKeqct::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    auto inst = std::make_shared<DispCompIeqcJeqcKeqct>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIeqcJeqcKeqct::initialize()
{
    DispCompIeqcJeqcKeqc::initialize();
    ppriIeJeKepXIpt = FullRow<double>::With(3);
    ppriIeJeKepEIpt = FullRow<double>::With(4);
    ppriIeJeKepXJpt = FullRow<double>::With(3);
    ppriIeJeKepEJpt = FullRow<double>::With(4);
    ppriIeJeKepEKpt = FullRow<double>::With(4);
}

void DispCompIeqcJeqcKeqct::initializeGlobally()
{
    //Do nothing.
}

void DispCompIeqcJeqcKeqct::calcPostDynCorrectorIteration()
{
    //"ppAjOIepEKpEK is not longer constant and must be set before any calculation."
    auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
    ppAjOKepEKpEK = efrmKqc->ppAjOepEpE(axisK);
    DispCompIeqcJeqcKeqc::calcPostDynCorrectorIteration();
}

void DispCompIeqcJeqcKeqct::preVelIC()
{
    Item::preVelIC();
    auto pAjOKept = std::static_pointer_cast<EndFrameqct>(efrmK)->pAjOept(axisK);
    priIeJeKept = pAjOKept->dot(rIeJeO);
}

double DispCompIeqcJeqcKeqct::pvaluept()
{
    return priIeJeKept;
}

FRowDsptr DispCompIeqcJeqcKeqct::ppvaluepXIpt()
{
    return ppriIeJeKepXIpt;
}

FRowDsptr DispCompIeqcJeqcKeqct::ppvaluepEIpt()
{
    return ppriIeJeKepEIpt;
}

FRowDsptr DispCompIeqcJeqcKeqct::ppvaluepEKpt()
{
    return ppriIeJeKepEKpt;
}

FRowDsptr DispCompIeqcJeqcKeqct::ppvaluepXJpt()
{
    return ppriIeJeKepXJpt;
}

FRowDsptr DispCompIeqcJeqcKeqct::ppvaluepEJpt()
{
    return ppriIeJeKepEJpt;
}

double DispCompIeqcJeqcKeqct::ppvalueptpt()
{
    return ppriIeJeKeptpt;
}

void DispCompIeqcJeqcKeqct::preAccIC()
{
    Item::preAccIC();
    auto pAjOKept = std::static_pointer_cast<EndFrameqct>(efrmK)->pAjOept(axisK);
    auto ppAjOKepEKTpt = std::static_pointer_cast<EndFrameqct>(efrmK)->ppAjOepETpt(axisK);
    auto ppAjOKeptpt = std::static_pointer_cast<EndFrameqct>(efrmK)->ppAjOeptpt(axisK);
    auto prIeJeOpEIT = std::static_pointer_cast<EndFrameqc>(eFrmI)->prOeOpE->transpose()->negated();
    auto prIeJeOpEJT = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE->transpose();
    for (size_t i = 0; i < 3; i++)
    {
        ppriIeJeKepXIpt->atiput(i, -(pAjOKept->at(i)));
        ppriIeJeKepXJpt->atiput(i, pAjOKept->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeKepEIpt->atiput(i, pAjOKept->dot(prIeJeOpEIT->at(i)));
        ppriIeJeKepEJpt->atiput(i, pAjOKept->dot(prIeJeOpEJT->at(i)));
        ppriIeJeKepEKpt->atiput(i, ppAjOKepEKTpt->at(i)->dot(rIeJeO));
    }
    ppriIeJeKeptpt = ppAjOKeptpt->dot(rIeJeO);
}
