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
    // Variables are constants.
    calcpVectorpXI();
    calcppVectorpEIpEI();
}

void MbD::DispIeqJeO::calcpVectorpXI()
{
    prIeJeOpXI = FullMatrix<double>::identitysptr(3)->negated();
}

void MbD::DispIeqJeO::calcpVectorpEI()
{
    prIeJeOpEI = frmIe->getprOeOpE()->negated();
}

void MbD::DispIeqJeO::calcppVectorpEIpEI()
{
    pprIeJeOpEIpEI = frmIe->getpprOeOpEpE()->negated();
}

FMatDsptr MbD::DispIeqJeO::getpVectorpXI()
{
    return prIeJeOpXI;
}

FMatDsptr MbD::DispIeqJeO::getpVectorpEI()
{
    return prIeJeOpEI;
}

FMatDsptr MbD::DispIeqJeO::getppCompipEIpEI(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(frmIe)->ppriOeOpEpE(axis)->negated();
}

void DispIeqJeO::simUpdateAll()
{
    // rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    // calcpVectorpXI() is a constant
    calcpVectorpEI();
}
