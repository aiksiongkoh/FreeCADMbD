/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIetJeqO.h"
#include "EndFrameq.h"
#include "EndFramet.h"

using namespace MbD;

std::shared_ptr<DispIetJeqO> DispIetJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIetJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIetJeqO::preVelIC()
{
    DispIeJeqO::preVelIC();
    calcpVectorpt();
}

void DispIetJeqO::preAccIC()
{
    DispIeJeqO::preAccIC();
    calcppVectorptpt();
}

FColDsptr DispIetJeqO::getpVectorpt()
{
    return prIeJeOpt;
}

FColDsptr DispIetJeqO::getppVectorptpt()
{
    return pprIeJeOptpt;
}

void DispIetJeqO::calcpVectorpt()
{
    prIeJeOpt = eFrmI->getprOeOpt()->negated();
}

void DispIetJeqO::calcppVectorptpt()
{
    // pprIeJeOptpt = std::dynamic_pointer_cast<EndFramet>(frmIe)->pprOeOptpt->negated();
    pprIeJeOptpt = eFrmI->getpprOeOptpt()->negated();
}
