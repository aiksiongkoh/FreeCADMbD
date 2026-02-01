/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIectJeqcKect.h"
#include "EndFramect.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIectJeqcKect> DispCompIectJeqcKect::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    assert(!frmi->has_qX());
    assert(frmj->has_qX());
    assert(!frmk->has_qX());
    auto inst = std::make_shared<DispCompIectJeqcKect>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIectJeqcKect::initialize()
{
    DispCompIecJeqcKec::initialize();
    ppriIeJeKepXJpt = FullRow<double>::With(3);
    ppriIeJeKepEJpt = FullRow<double>::With(4);
}

FRowDsptr DispCompIectJeqcKect::ppvaluepXJpt()
{
    return ppriIeJeKepXJpt;
}

FRowDsptr DispCompIectJeqcKect::ppvaluepEJpt()
{
    return ppriIeJeKepEJpt;
}

double DispCompIectJeqcKect::ppvalueptpt()
{
    return ppriIeJeKeptpt;
}

double DispCompIectJeqcKect::pvaluept()
{
    return priIeJeKept;
}

void DispCompIectJeqcKect::preAccIC()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //riIeJeKe = aArowiKeO dot rIeJeO = aAcoljOKe dot rIeJeO
    //priIeJeKept = pAjOKept dot rIeJeO + aAjOKe dot prIeJeOpt
    //ppriIeJeKeptpt = ppAjOKeptpt dot rIeJeO + 2.0*(pAjOKept dot prIeJeOpt) + aAjOKe dot pprIeJeOptpt
    DispCompIecJeqcKec::preAccIC();
    auto pAjOKept = std::static_pointer_cast<EndFramect>(efrmK)->pAjOept(axisK);
    for (size_t i = 0; i < 3; i++)
    {
        ppriIeJeKepXJpt->atiput(i, pAjOKept->at(i));
    }
    auto prIeJeOpEJT = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeKepEJpt->atiput(i, pAjOKept->dot(prIeJeOpEJT->at(i)));
    }
    auto ppAjOKeptpt = std::static_pointer_cast<EndFramect>(efrmK)->ppAjOeptpt(axisK);
    ppriIeJeKeptpt = ppAjOKeptpt->dot(rIeJeO);
    auto eFrmIct = std::static_pointer_cast<EndFramect>(eFrmI);
    auto prIeJeOpt = eFrmIct->prOeOpt->negated();
    auto pprIeJeOptpt = eFrmIct->pprOeOptpt->negated();
    ppriIeJeKeptpt += (2.0 * pAjOKept->dot(prIeJeOpt)) + aAjOKe->dot(pprIeJeOptpt);
}

void DispCompIectJeqcKect::preVelIC()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //riIeJeKe = aArowiKeO dot rIeJeO = aAcoljOKe dot rIeJeO
    //priIeJeKept = pAjOKept dot rIeJeO + aAjOKe dot prIeJeOpt
    DispCompIecJeqcKec::preVelIC();
    auto pAjOKept = std::static_pointer_cast<EndFramect>(efrmK)->pAjOept(axisK);
    auto prIeJeOpt = std::static_pointer_cast<EndFramect>(eFrmI)->prOeOpt->negated();
    priIeJeKept = pAjOKept->dot(rIeJeO) + aAjOKe->dot(prIeJeOpt);
}
