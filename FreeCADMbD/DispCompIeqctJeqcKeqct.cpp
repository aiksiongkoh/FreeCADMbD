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
    auto inst = std::make_shared<DispCompIeqctJeqcKeqct>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIeqctJeqcKeqct::preVelIC()
{
    DispCompIeqcJeqcKeqct::preVelIC();
    auto& mprIeJeOpt = std::static_pointer_cast<EndFrameqct>(eFrmI)->prOeOpt;
    priIeJeKept -= aAjOKe->dot(mprIeJeOpt);
}

void DispCompIeqctJeqcKeqct::preAccIC()
{
    DispCompIeqcJeqcKeqct::preAccIC();
    auto pAjOKept = std::static_pointer_cast<EndFrameqct>(efrmK)->pAjOept(axisK);
    auto eFrmIqct = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto& mprIeJeOpt = eFrmIqct->prOeOpt;
    auto mpprIeJeOpEITpt = eFrmIqct->pprOeOpEpt->transpose();
    auto& mpprIeJeOptpt = eFrmIqct->pprOeOptpt;
    for (size_t i = 0; i < 4; i++)
    {
        ppriIeJeKepEIpt->atiminusNumber(i, aAjOKe->dot(mpprIeJeOpEITpt->at(i)));
        ppriIeJeKepEKpt->atiminusNumber(i, pAjOKepEKT->at(i)->dot(mprIeJeOpt));
    }
    ppriIeJeKeptpt +=  -(2.0 * pAjOKept->dot(mprIeJeOpt)) - aAjOKe->dot(mpprIeJeOptpt);
}
