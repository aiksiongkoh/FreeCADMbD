/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIetJeqO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIetJeqO> DispIetJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIetJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIetJeqO::initializeGlobally()
{
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->pprOeOpEpE;
}

void MbD::DispIetJeqO::preVelIC()
{
    DispIecJeqcO::preVelIC();
    calcpvaluept();
}

void MbD::DispIetJeqO::preAccIC()
{
    DispIecJeqcO::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}

FMatDsptr MbD::DispIetJeqO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIetJeqO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

FColDsptr MbD::DispIetJeqO::getprIeJeOpt()
{
    return prIeJeOpt;
}

FColDsptr MbD::DispIetJeqO::getpprIeJeOptpt()
{
    return pprIeJeOptpt;
}

void DispIetJeqO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIecJecO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE;
}
