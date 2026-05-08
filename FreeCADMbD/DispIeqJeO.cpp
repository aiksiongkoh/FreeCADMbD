/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeO.h"
#include "EndFrameq.h"

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

void DispIeqJeO::calcpVectorpXI()
{
    prIeJeOpXI = FullMatrix<double>::identitysptr(3)->negated();
}

void DispIeqJeO::calcpVectorpEI()
{
    prIeJeOpEI = eFrmI->getprOeOpE()->negated();
}

void DispIeqJeO::calcppVectorpEIpEI()
{
    pprIeJeOpEIpEI = eFrmI->getpprOeOpEpE()->negated();
}

FMatDsptr DispIeqJeO::getpVectorpXI()
{
    return prIeJeOpXI;
}

FMatDsptr DispIeqJeO::getpVectorpEI()
{
    return prIeJeOpEI;
}

FMatFColDsptr DispIeqJeO::getppVectorpEIpEI()
{
    return pprIeJeOpEIpEI;
}

FMatDsptr DispIeqJeO::getppCompipEIpEI(size_t axis)
{
    return std::static_pointer_cast<EndFrameq>(eFrmI)->ppriOeOpEpE(axis)->negated();
}

void DispIeqJeO::simUpdateAll()
{
    // rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    // calcpVectorpXI() is a constant
    calcpVectorpEI();
}
