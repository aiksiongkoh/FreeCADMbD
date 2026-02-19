/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeJeqKe> DispIeJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeJeqKe::initializeGlobally()
{
    //Variables are constants.
}
