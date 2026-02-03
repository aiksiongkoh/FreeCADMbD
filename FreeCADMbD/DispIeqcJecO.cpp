/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqcJecO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqcJecO> DispIeqcJecO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqcJecO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqcJecO::initializeGlobally()
{
    DispIecJecO::initializeGlobally();
    //Variables are constants.
    prIeJeOpXI = FullMatrix<double>::identitysptr(3)->negated();
    pprIeJeOpEIpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->pprOeOpEpE->negated();
}

FMatDsptr MbD::DispIeqcJecO::getprIeJeOpXI()
{
    return prIeJeOpXI;
}

FMatDsptr MbD::DispIeqcJecO::getprIeJeOpEI()
{
    return prIeJeOpEI;
}

FMatDsptr MbD::DispIeqcJecO::getppriIeJeOpEIpEI(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(eFrmI)->ppriOeOpEpE(axis)->negated();
}

FMatDsptr MbD::DispIeqcJecO::getppriIeJeOpEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppriOeOpEpE(axis);
}

void DispIeqcJecO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIecJecO::simUpdateAll();
    prIeJeOpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->prOeOpE->negated();
}
