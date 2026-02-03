/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqctJeqcIe.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DispCompIeqctJeqcIe> DispCompIeqctJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIeqctJeqcIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIeqctJeqcIe::initialize()
{
    DispCompIeqcJeqcIe::initialize();
    ppriIeJeIepXIpt = FullRow<double>::With(3);
    ppriIeJeIepEIpt = FullRow<double>::With(4);
    ppriIeJeIepXJpt = FullRow<double>::With(3);
    ppriIeJeIepEJpt = FullRow<double>::With(4);
}

void DispCompIeqctJeqcIe::calcppvaluepEIpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto ppAjOIepEITpt = frmIeqct->ppAjOepETpt(axis);
    auto mprIeJeOpEIT = frmIeqct->prOeOpE->transpose();
    auto mpprIeJeOpEITpt = frmIeqct->pprOeOpEpt->transpose();
    auto mprIeJeOpt = frmIeqct->prOeOpt;
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAjOIepEITpti = ppAjOIepEITpt->at(i);
        auto pAjOIepEITi = pAjOIepEIT->at(i);
        auto mprIeJeOpEITi = mprIeJeOpEIT->at(i);
        auto mpprIeJeOpEITpti = mpprIeJeOpEITpt->at(i);
        auto ppriIeJeIepEIpti = ppAjOIepEITpti->dot(rIeJeO) - pAjOIepEITi->dot(mprIeJeOpt) - pAjOIept->dot(mprIeJeOpEITi) - aAjOIe->dot(mpprIeJeOpEITpti);
        ppriIeJeIepEIpt->atiput(i, ppriIeJeIepEIpti);
    }
}

void DispCompIeqctJeqcIe::calcppvaluepEJpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto frmJeqct = std::static_pointer_cast<EndFrameqct>(eFrmJ);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto prIeJeOpEJT = frmJeqct->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeIepEJpt->atiput(i, pAjOIept->dot(prIeJeOpEJT->at(i)));
    }
}

void DispCompIeqctJeqcIe::calcppvalueptpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto ppAjOIeptpt = frmIeqct->ppAjOeptpt(axis);
    auto mprIeJeOpt = frmIeqct->prOeOpt;
    auto mpprIeJeOptpt = frmIeqct->pprOeOptpt;
    ppriIeJeIeptpt = ppAjOIeptpt->dot(rIeJeO) - pAjOIept->dot(mprIeJeOpt) - pAjOIept->dot(mprIeJeOpt) - aAjOIe->dot(mpprIeJeOptpt);
}

void DispCompIeqctJeqcIe::calcppvaluepXIpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    for (size_t i = 0; i < 3; i++)
    {
        ppriIeJeIepXIpt->atiput(i, -pAjOIept->at(i));
    }
}

void DispCompIeqctJeqcIe::calcppvaluepXJpt()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    for (size_t i = 0; i < 3; i++)
    {
        ppriIeJeIepXJpt->atiput(i, pAjOIept->at(i));
    }
}

void DispCompIeqctJeqcIe::calcpvaluept()
{
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto pAjOIept = frmIeqct->pAjOept(axis);
    auto mprIeJeOpt = frmIeqct->prOeOpt;
    priIeJeIept = pAjOIept->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpt);
}

void DispCompIeqctJeqcIe::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeIe = aAIeO * rIeJeO
    //riIeJeIe = aArowiIeO dot rIeJeO = aAcoljOIe dot rIeJeO
    //"ppAjOIepEIpEI is not longer constant and must be set before any calculation."
    auto frmIeqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    ppAjOIepEIpEI = frmIeqct->ppAjOepEpE(axis);
    DispCompIeqcJeqcIe::simUpdateAll();
}

void DispCompIeqctJeqcIe::initializeGlobally()
{
    //"Do nothing."
}

void DispCompIeqctJeqcIe::preAccIC()
{
    DispCompIeqcJeqcIe::preAccIC();
    calcppvaluepXIpt();
    calcppvaluepEIpt();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}

void DispCompIeqctJeqcIe::preVelIC()
{
    DispCompIeqcJeqcIe::preVelIC();
    calcpvaluept();
}

FRowDsptr DispCompIeqctJeqcIe::ppvaluepEIpt()
{
    return ppriIeJeIepEIpt;
}

FRowDsptr DispCompIeqctJeqcIe::ppvaluepEJpt()
{
    return ppriIeJeIepEJpt;
}

double DispCompIeqctJeqcIe::ppvalueptpt()
{
    return ppriIeJeIeptpt;
}

FRowDsptr DispCompIeqctJeqcIe::ppvaluepXIpt()
{
    return ppriIeJeIepXIpt;
}

FRowDsptr DispCompIeqctJeqcIe::ppvaluepXJpt()
{
    return ppriIeJeIepXJpt;
}

double DispCompIeqctJeqcIe::pvaluept()
{
    return priIeJeIept;
}
