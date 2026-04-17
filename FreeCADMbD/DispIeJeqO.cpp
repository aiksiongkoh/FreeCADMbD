/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeJeqO> DispIeJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeJeqO::initializeGlobally()
{
    DispIeJeO::initializeGlobally();
    // Variables are constants.
    calcpVectorpXJ();
    calcppVectorpEJpEJ();
}

void MbD::DispIeJeqO::calcpVectorpXJ()
{
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
}

void MbD::DispIeJeqO::calcpVectorpEJ()
{
    // rIeJeO = rOJeO - rOIeO
    prIeJeOpEJ = frmJe->getprOeOpE();
}

void MbD::DispIeJeqO::calcppVectorpEJpEJ()
{
    pprIeJeOpEJpEJ = frmJe->getpprOeOpEpE();
}

FMatDsptr MbD::DispIeJeqO::getpVectorpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeJeqO::getpVectorpEJ()
{
    return prIeJeOpEJ;
}

void DispIeJeqO::simUpdateAll()
{
    // rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    // calcpVectorpXJ() is a constant
    calcpVectorpEJ();
}

FMatDsptr MbD::DispIeJeqO::getppCompipEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(frmJe)->ppriOeOpEpE(axis);
}
