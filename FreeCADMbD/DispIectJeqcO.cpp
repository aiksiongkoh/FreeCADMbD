/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIectJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIectJeqcO> DispIectJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIectJeqcO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIectJeqcO::initializeGlobally()
{
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->pprOeOpEpE;
}

void MbD::DispIectJeqcO::preVelIC()
{
    DispIecJeqcO::preVelIC();
    calcpvaluept();
}

void MbD::DispIectJeqcO::preAccIC()
{
    DispIecJeqcO::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}

FMatDsptr MbD::DispIectJeqcO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIectJeqcO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

FColDsptr MbD::DispIectJeqcO::getprIeJeOpt()
{
    return prIeJeOpt;
}

FColDsptr MbD::DispIectJeqcO::getpprIeJeOptpt()
{
    return pprIeJeOptpt;
}

void DispIectJeqcO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIecJecO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE;
}
