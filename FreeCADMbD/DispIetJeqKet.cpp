/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIetJeqKet.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIetJeqKet> DispIetJeqKet::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIetJeqKet>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIetJeqKet::initializeGlobally()
{
    //Variables are constants.
}

void MbD::DispIetJeqKet::preVelIC()
{
    DispIeJeqKe::preVelIC();
    calcpvaluept();
}

void MbD::DispIetJeqKet::preAccIC()
{
    DispIeJeqKe::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}
