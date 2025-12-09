/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeqctJeqc> DirectionCosineIeqctJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIeqctJeqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIeqctJeqc::initialize()
{
    DirectionCosineIeqcJeqc::initialize();
    ppAijIeJepEIpt = FullRow<double>::With(4);
    ppAijIeJepEJpt = FullRow<double>::With(4);
}

void DirectionCosineIeqctJeqc::initializeGlobally()
{
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppAjOepEpE(axisJ);
}

FRowDsptr DirectionCosineIeqctJeqc::ppvaluepEIpt()
{
    return ppAijIeJepEIpt;
}

FRowDsptr DirectionCosineIeqctJeqc::ppvaluepEJpt()
{
    return ppAijIeJepEJpt;
}

double DirectionCosineIeqctJeqc::ppvalueptpt()
{
    return ppAijIeJeptpt;
}

void DirectionCosineIeqctJeqc::calcPostDynCorrectorIteration()
{
    //"ppAjOIepEIpEI is not longer constant and must be set before any calculation."

    ppAjOIepEIpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->ppAjOepEpE(axisI);
    DirectionCosineIeqcJeqc::calcPostDynCorrectorIteration();
}

void DirectionCosineIeqctJeqc::preVelIC()
{
    Item::preVelIC();
    auto pAjOIept = std::static_pointer_cast<EndFrameqct>(eFrmI)->pAjOept(axisI);
    pAijIeJept = pAjOIept->dot(aAjOJe);
}

double DirectionCosineIeqctJeqc::pvaluept()
{
    return pAijIeJept;
}

void DirectionCosineIeqctJeqc::preAccIC()
{
    //| ppAjOIepEITpt ppAjOIeptpt ppAjOIepEITpti pAjOIept |
    Item::preAccIC();
    auto pAjOIept = std::static_pointer_cast<EndFrameqct>(eFrmI)->pAjOept(axisI);
    auto ppAjOIepEITpt = std::static_pointer_cast<EndFrameqct>(eFrmI)->ppAjOepETpt(axisI);
    auto ppAjOIeptpt = std::static_pointer_cast<EndFrameqct>(eFrmI)->ppAjOeptpt(axisI);
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppAjOIepEITpti = ppAjOIepEITpt->at(i);
        ppAijIeJepEIpt->atiput(i, ppAjOIepEITpti->dot(aAjOJe));
    }
    for (size_t i = 0; i < 4; i++)
    {
        ppAijIeJepEJpt->atiput(i, pAjOIept->dot(pAjOJepEJT->at(i)));
    }
    ppAijIeJeptpt = ppAjOIeptpt->dot(aAjOJe);
}
