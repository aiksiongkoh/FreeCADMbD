/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineIetJeq.h"
#include "EndFrameq.h"
#include "EndFramet.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIetJeq> DirectionCosineIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIetJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIetJeq::initialize()
{
    DirectionCosineIeJeq::initialize();
    ppAijIeJepEJpt = FullRow<double>::With(4);
}

void DirectionCosineIetJeq::initializeGlobally()
{
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameq>(eFrmJ)->ppAjOepEpE(axisJ);
}

void DirectionCosineIetJeq::simUpdateAll()
{
    DirectionCosineIeJeq::simUpdateAll();
}

FRowDsptr DirectionCosineIetJeq::ppvaluepEJpt()
{
    return ppAijIeJepEJpt;
}

double DirectionCosineIetJeq::ppvalueptpt()
{
    return ppAijIeJeptpt;
}

void DirectionCosineIetJeq::preVelIC()
{
    Item::preVelIC();
    auto pAjOIept = std::static_pointer_cast<EndFramet>(eFrmI)->pAjOept(axisI);
    pAijIeJept = pAjOIept->dot(aAjOJe);
}

double DirectionCosineIetJeq::pvaluept()
{
    return pAijIeJept;
}

void DirectionCosineIetJeq::preAccIC()
{
    //| ppAjOIepEITpt ppAjOIeptpt ppAjOIepEITpti pAjOIept |
    Item::preAccIC();
    auto pAjOIept = std::static_pointer_cast<EndFramet>(eFrmI)->pAjOept(axisI);
    auto ppAjOIeptpt = std::static_pointer_cast<EndFramet>(eFrmI)->ppAjOeptpt(axisI);
    for (size_t i = 0; i < 4; i++)
    {
        ppAijIeJepEJpt->atiput(i, pAjOIept->dot(pAjOJepEJT->at(i)));
    }
    ppAijIeJeptpt = ppAjOIeptpt->dot(aAjOJe);
}
