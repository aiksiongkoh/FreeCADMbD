/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeKeq> DispIeqJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeKeq::initializeGlobally()
{
    DispIeJeKe::initializeGlobally();
    //Variables are constants.
}

void MbD::DispIeqJeKeq::calcpvaluepEK()
{
    prIeJeKepEK = frmKe->pAOepEtimesFullColumn(rIeJeO);
}
