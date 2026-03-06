/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeqKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqKeq> DispIeqJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeqKeq::initializeGlobally()
{
    DispIeqJeKe::initializeGlobally();
    //Variables are constants.
}

void MbD::DispIeqJeqKeq::calcpvaluepEK()
{
    prIeJeKepEK = frmKe->pAOepEtimesFullColumn(rIeJeO);
}
