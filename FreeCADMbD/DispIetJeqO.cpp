/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIetJeqO.h"
#include "EndFrameqc.h"
#include "EndFramect.h"

using namespace MbD;

std::shared_ptr<DispIetJeqO> DispIetJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIetJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIetJeqO::simUpdateAll()
{
    DispIeJeqO::simUpdateAll();
    calcpVectorpt();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorptpt();
}

void MbD::DispIetJeqO::preVelIC()
{
    DispIeJeqO::preVelIC();
    calcpVectorpt();
}

void MbD::DispIetJeqO::preAccIC()
{
    DispIeJeqO::preAccIC();
    calcppVectorptpt();
}

FMatDsptr MbD::DispIetJeqO::getpVectorpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIetJeqO::getpVectorpEJ()
{
    return prIeJeOpEJ;
}

FColDsptr MbD::DispIetJeqO::getpVectorpt()
{
    return prIeJeOpt;
}

FColDsptr MbD::DispIetJeqO::getppVectorptpt()
{
    return pprIeJeOptpt;
}

void DispIetJeqO::calcpVectorpt()
{
    prIeJeOpt = frmIe->getprOeOpt()->negated();
}

void DispIetJeqO::calcppVectorptpt()
{
    // pprIeJeOptpt = std::dynamic_pointer_cast<EndFramect>(frmIe)->pprOeOptpt->negated();
    pprIeJeOptpt = frmIe->getpprOeOptpt()->negated();
}
