/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeqO.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqO> DispIeqJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeqO::initializeGlobally()
{
    DispIeqJeO::initializeGlobally();
    // Variables are constants.
    calcpVectorpXJ();
    calcppVectorpEJpEJ();
}

void DispIeqJeqO::calcpVectorpXJ()
{
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
}

void DispIeqJeqO::calcpVectorpEJ()
{
    // rIeJeO = rOJeO - rOIeO
    prIeJeOpEJ = eFrmJ->getprOeOpE();
}

void DispIeqJeqO::calcppVectorpEJpEJ()
{
    pprIeJeOpEJpEJ = eFrmJ->getpprOeOpEpE();
}

FMatDsptr DispIeqJeqO::getpVectorpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr DispIeqJeqO::getpVectorpEJ()
{
    return prIeJeOpEJ;
}

FMatFColDsptr DispIeqJeqO::getppVectorpEJpEJ()
{
    return pprIeJeOpEJpEJ;
}

void DispIeqJeqO::simUpdateAll()
{
    // rIeJeO = rOJeO - rOIeO
    DispIeqJeO::simUpdateAll();
    // calcpVectorpXJ() is a constant
    calcpVectorpEJ();
}

FMatDsptr DispIeqJeqO::getppCompipEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameq>(eFrmJ)->ppriOeOpEpE(axis);
}
