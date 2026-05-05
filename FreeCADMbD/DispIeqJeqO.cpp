/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeqO.h"
#include "EndFrameqc.h"

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

void MbD::DispIeqJeqO::calcpVectorpXJ()
{
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
}

void MbD::DispIeqJeqO::calcpVectorpEJ()
{
    // rIeJeO = rOJeO - rOIeO
    prIeJeOpEJ = eFrmJ->getprOeOpE();
}

void MbD::DispIeqJeqO::calcppVectorpEJpEJ()
{
    pprIeJeOpEJpEJ = eFrmJ->getpprOeOpEpE();
}

FMatDsptr MbD::DispIeqJeqO::getpVectorpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeqJeqO::getpVectorpEJ()
{
    return prIeJeOpEJ;
}

FMatFColDsptr MbD::DispIeqJeqO::getppVectorpEJpEJ()
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

FMatDsptr MbD::DispIeqJeqO::getppCompipEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppriOeOpEpE(axis);
}
