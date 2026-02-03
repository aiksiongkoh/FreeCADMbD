/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIecJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIecJeqcO> DispIecJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIecJeqcO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIecJeqcO::initializeGlobally()
{
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->pprOeOpEpE;
}

FMatDsptr MbD::DispIecJeqcO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIecJeqcO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

void DispIecJeqcO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIecJecO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE;
}
