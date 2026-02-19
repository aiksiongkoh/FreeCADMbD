/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeqKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqKe> DispIeqJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeqKe::initializeGlobally()
{
    DispIeqJeKe::initializeGlobally();
    //Variables are constants.
}
