/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqO> DispIeqtJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqtJeqO::initializeGlobally()
{
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(frmJe)->pprOeOpEpE;
}

void MbD::DispIeqtJeqO::preVelIC()
{
    DispIeqJeqO::preVelIC();
    calcpvaluept();
}

void MbD::DispIeqtJeqO::preAccIC()
{
    DispIeqJeqO::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}

FMatDsptr MbD::DispIeqtJeqO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeqtJeqO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

FColDsptr MbD::DispIeqtJeqO::getprIeJeOpt()
{
    return prIeJeOpt;
}

FColDsptr MbD::DispIeqtJeqO::getpprIeJeOptpt()
{
    return pprIeJeOptpt;
}
