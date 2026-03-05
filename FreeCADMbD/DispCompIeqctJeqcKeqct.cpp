/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqctJeqcKeqct.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DispCompIeqctJeqcKeqct> DispCompIeqctJeqcKeqct::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    assert(frmi->has_qX());
    assert(frmj->has_qX());
    assert(frmk->has_qX());
    auto inst = std::make_shared<DispCompIeqctJeqcKeqct>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIeqctJeqcKeqct::preVelIC()
{
    DispCompIeqcJeqcKeqct::preVelIC();
    auto prIeJeOpt = std::static_pointer_cast<EndFrameqct>(eFrmI)->prOeOpt->negated();
    priIeJeKept += aAjOKe->dot(prIeJeOpt);
}

void DispCompIeqctJeqcKeqct::preAccIC()
{
    DispCompIeqcJeqcKeqct::preAccIC();
    auto pAjOKept = std::static_pointer_cast<EndFrameqct>(efrmK)->pAjOept(axisK);
    auto eFrmIqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto prIeJeOpt = eFrmIqct->prOeOpt->negated();
    auto pprIeJeOpEITpt = eFrmIqct->pprOeOpEpt->transpose()->negated();
    auto pprIeJeOptpt = eFrmIqct->pprOeOptpt->negated();
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeKepEIpt->atiplusNumber(i, aAjOKe->dot(pprIeJeOpEITpt->at(i)));
        ppriIeJeKepEKpt->atiplusNumber(i, pAjOKepEKT->at(i)->dot(prIeJeOpt));
    }
    ppriIeJeKeptpt +=  (2.0 * pAjOKept->dot(prIeJeOpt)) + aAjOKe->dot(pprIeJeOptpt);
}
