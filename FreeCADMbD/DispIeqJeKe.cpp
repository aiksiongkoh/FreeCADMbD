/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeKe> DispIeqJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeKe::initializeGlobally()
{
    DispIeJeKe::initializeGlobally();
    //Variables are constants.
}

void MbD::DispIeqJeKe::calcpvaluepXI()
{
    prIeJeKepXI = frmKe->aAOe->transposeTimesFullMatrix(getprIeJeOpXI());
}
