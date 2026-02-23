/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeO> DispIeqJeO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeO::initializeGlobally()
{
    DispIeJeO::initializeGlobally();
    //Variables are constants.
    prIeJeOpXI = FullMatrix<double>::identitysptr(3)->negated();
    pprIeJeOpEIpEI = std::static_pointer_cast<EndFrameqc>(frmIe)->pprOeOpEpE->negated();
}

FMatDsptr MbD::DispIeqJeO::getprIeJeOpXI()
{
    return prIeJeOpXI;
}

FMatDsptr MbD::DispIeqJeO::getprIeJeOpEI()
{
    return prIeJeOpEI;
}

FMatDsptr MbD::DispIeqJeO::getppriIeJeOpEIpEI(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(frmIe)->ppriOeOpEpE(axis)->negated();
}

void DispIeqJeO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    prIeJeOpEI = std::static_pointer_cast<EndFrameqc>(frmIe)->prOeOpE->negated();
}
