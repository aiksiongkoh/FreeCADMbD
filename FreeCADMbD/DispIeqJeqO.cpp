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
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->pprOeOpEpE;
}

FMatDsptr MbD::DispIeqJeqO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeqJeqO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

void DispIeqJeqO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIeqJeO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->prOeOpE;
}

FMatDsptr MbD::DispIeqJeqO::getppriIeJeOpEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(frmJe)->ppriOeOpEpE(axis);
}
