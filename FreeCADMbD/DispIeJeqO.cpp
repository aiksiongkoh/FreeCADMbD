/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqO.h"
#include "EndFrameq.h"

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

void DispIeJeqO::calcpVectorpXJ()
{
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
}

void DispIeJeqO::calcpVectorpEJ()
{
    // rIeJeO = rOJeO - rOIeO
    prIeJeOpEJ = eFrmJ->getprOeOpE();
}

void DispIeJeqO::calcppVectorpEJpEJ()
{
    pprIeJeOpEJpEJ = eFrmJ->getpprOeOpEpE();
}

FMatDsptr DispIeJeqO::getpVectorpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr DispIeJeqO::getpVectorpEJ()
{
    return prIeJeOpEJ;
}

FMatFColDsptr DispIeJeqO::getppVectorpEJpEJ()
{
    return pprIeJeOpEJpEJ;
}

void DispIeJeqO::simUpdateAll()
{
    // rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    // calcpVectorpXJ() is a constant
    calcpVectorpEJ();
}

FMatDsptr DispIeJeqO::getppCompipEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameq>(eFrmJ)->ppriOeOpEpE(axis);
}
