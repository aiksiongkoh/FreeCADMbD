/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineIectJeqc.h"
#include "EndFrameqc.h"
#include "EndFramect.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIectJeqc> DirectionCosineIectJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIectJeqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIectJeqc::initialize()
{
    DirectionCosineIecJeqc::initialize();
    ppAijIeJepEJpt = FullRow<double>::With(4);
}

void DirectionCosineIectJeqc::initializeGlobally()
{
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppAjOepEpE(axisJ);
}

FRowDsptr DirectionCosineIectJeqc::ppvaluepEJpt()
{
    return ppAijIeJepEJpt;
}

double DirectionCosineIectJeqc::ppvalueptpt()
{
    return ppAijIeJeptpt;
}

void DirectionCosineIectJeqc::preVelIC()
{
    Item::preVelIC();
    auto pAjOIept = std::static_pointer_cast<EndFramect>(eFrmI)->pAjOept(axisI);
    pAijIeJept = pAjOIept->dot(aAjOJe);
}

double DirectionCosineIectJeqc::pvaluept()
{
    return pAijIeJept;
}

void DirectionCosineIectJeqc::preAccIC()
{
    //| ppAjOIepEITpt ppAjOIeptpt ppAjOIepEITpti pAjOIept |
    Item::preAccIC();
    auto pAjOIept = std::static_pointer_cast<EndFramect>(eFrmI)->pAjOept(axisI);
    auto ppAjOIeptpt = std::static_pointer_cast<EndFramect>(eFrmI)->ppAjOeptpt(axisI);
    for (size_t i = 0; i < 4; i++)
    {
        ppAijIeJepEJpt->atiput(i, pAjOIept->dot(pAjOJepEJT->at(i)));
    }
    ppAijIeJeptpt = ppAjOIeptpt->dot(aAjOJe);
}
