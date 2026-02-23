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

void DispIetJeqO::initializeGlobally()
{
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->pprOeOpEpE;
}

void MbD::DispIetJeqO::preVelIC()
{
    DispIeJeqO::preVelIC();
    calcpvaluept();
}

void MbD::DispIetJeqO::preAccIC()
{
    DispIeJeqO::preAccIC();
    calcppvalueptpt();
}

FMatDsptr MbD::DispIetJeqO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIetJeqO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

FColDsptr MbD::DispIetJeqO::getprIeJeOpt()
{
    return prIeJeOpt;
}

FColDsptr MbD::DispIetJeqO::getpprIeJeOptpt()
{
    return pprIeJeOptpt;
}

void DispIetJeqO::calcpvaluept()
{
    prIeJeOpt = std::dynamic_pointer_cast<EndFramect>(frmIe)->prOeOpt->negated();
}

void DispIetJeqO::calcppvalueptpt()
{
    pprIeJeOptpt = std::dynamic_pointer_cast<EndFramect>(frmIe)->pprOeOptpt->negated();
}
