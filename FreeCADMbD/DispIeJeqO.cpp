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
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->pprOeOpEpE;
}

FMatDsptr MbD::DispIeJeqO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeJeqO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

void DispIeJeqO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIeJeO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->prOeOpE;
}

FMatDsptr MbD::DispIeJeqO::getppriIeJeOpEJpEJ(size_t axis)
{
    return std::static_pointer_cast<EndFrameqc>(frmJe)->ppriOeOpEpE(axis);
}
