/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineIeqtJeq.h"
#include "EndFrameq.h"
#include "EndFrameqt.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeqtJeq> DirectionCosineIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIeqtJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIeqtJeq::initialize()
{
    DirectionCosineIeqJeq::initialize();
    ppAijIeJepEIpt = FullRow<double>::With(4);
    ppAijIeJepEJpt = FullRow<double>::With(4);
}

void DirectionCosineIeqtJeq::initializeGlobally()
{
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameq>(eFrmJ)->ppAjOepEpE(axisJ);
}

FRowDsptr DirectionCosineIeqtJeq::ppvaluepEIpt()
{
    return ppAijIeJepEIpt;
}

FRowDsptr DirectionCosineIeqtJeq::ppvaluepEJpt()
{
    return ppAijIeJepEJpt;
}

double DirectionCosineIeqtJeq::ppvalueptpt()
{
    return ppAijIeJeptpt;
}

void DirectionCosineIeqtJeq::simUpdateAll()
{
    //cos(the) = aAijIeJe = aAcoliOIe->dot(aAcoljOJe);
    //"ppAjOIepEIpEI is not longer constant and must be set before any calculation."

    ppAjOIepEIpEI = std::static_pointer_cast<EndFrameq>(eFrmI)->ppAjOepEpE(axisI);
    DirectionCosineIeqJeq::simUpdateAll();
}

void DirectionCosineIeqtJeq::preVelIC()
{
    Item::preVelIC();
    auto pAjOIept = std::static_pointer_cast<EndFrameqt>(eFrmI)->pAjOept(axisI);
    pAijIeJept = pAjOIept->dot(aAjOJe);
}

double DirectionCosineIeqtJeq::pvaluept()
{
    return pAijIeJept;
}

void DirectionCosineIeqtJeq::preAccIC()
{
    //| ppAjOIepEITpt ppAjOIeptpt ppAjOIepEITpti pAjOIept |
    Item::preAccIC();
    auto pAjOIept = std::static_pointer_cast<EndFrameqt>(eFrmI)->pAjOept(axisI);
    auto ppAjOIepEITpt = std::static_pointer_cast<EndFrameqt>(eFrmI)->ppAjOepETpt(axisI);
    auto ppAjOIeptpt = std::static_pointer_cast<EndFrameqt>(eFrmI)->ppAjOeptpt(axisI);
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAjOIepEITpti = ppAjOIepEITpt->at(i);
        ppAijIeJepEIpt->atiput(i, ppAjOIepEITpti->dot(aAjOJe));
    }
    for (size_t i = 0; i < 4; i++)
    {
        ppAijIeJepEJpt->atiput(i, pAjOIept->dot(pAjOJepEJT->at(i)));
    }
    ppAijIeJeptpt = ppAjOIeptpt->dot(aAjOJe);
}
