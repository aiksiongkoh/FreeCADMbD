/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIectJeqcIe.h"
#include "EndFramect.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIectJeqcIe> DispCompIectJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIectJeqcIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIectJeqcIe::initialize()
{
    DispCompIecJeqcIe::initialize();
    ppriIeJeIepXJpt = FullRow<double>::With(3);
    ppriIeJeIepEJpt = FullRow<double>::With(4);
}

void DispCompIectJeqcIe::calcppvaluepEJpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFramect>(eFrmI);
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto prIeJeOpEJT = frmJeqc->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeIepEJpt->atiput(i, pAjOIept->dot(prIeJeOpEJT->at(i)));
    }
}

void DispCompIectJeqcIe::calcppvalueptpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFramect>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto ppAjOIeptpt = frmIeqct->ppAjOeptpt(axis);
    auto mprIeJeOpt = frmIeqct->prOeOpt;
    auto mpprIeJeOptpt = frmIeqct->pprOeOptpt;
    ppriIeJeIeptpt = ppAjOIeptpt->dot(rIeJeO) - pAjOIept->dot(mprIeJeOpt) - pAjOIept->dot(mprIeJeOpt) - aAjOIe->dot(mpprIeJeOptpt);
}

void DispCompIectJeqcIe::calcppvaluepXJpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFramect>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    for (size_t i = 0; i < 3; i++)
    {
        ppriIeJeIepXJpt->atiput(i, pAjOIept->at(i));
    }
}

void DispCompIectJeqcIe::calcpvaluept()
{
    auto frmIeqct = std::static_pointer_cast<EndFramect>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto mprIeJeOpt = frmIeqct->prOeOpt;
    priIeJeIept = pAjOIept->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpt);
}

void DispCompIectJeqcIe::initializeGlobally()
{
    //"Do nothing."
}

void DispCompIectJeqcIe::preAccIC()
{
    Item::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}

void DispCompIectJeqcIe::preVelIC()
{
    Item::preVelIC();
    calcpvaluept();
}

FRowDsptr DispCompIectJeqcIe::ppvaluepEJpt()
{
    return ppriIeJeIepEJpt;
}

double DispCompIectJeqcIe::ppvalueptpt()
{
    return ppriIeJeIeptpt;
}

FRowDsptr DispCompIectJeqcIe::ppvaluepXJpt()
{
    return ppriIeJeIepXJpt;
}

double DispCompIectJeqcIe::pvaluept()
{
    return priIeJeIept;
}
