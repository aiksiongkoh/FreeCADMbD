/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqcJeqcO> DispIeqcJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqcJeqcO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqcJeqcO::initializeGlobally()
{
    DispIeqcJecO::initializeGlobally();
    //Variables are constants.
    prIeJeOpXJ = FullMatrix<double>::identitysptr(3);
    pprIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->pprOeOpEpE;
}

FMatDsptr MbD::DispIeqcJeqcO::getprIeJeOpXJ()
{
    return prIeJeOpXJ;
}

FMatDsptr MbD::DispIeqcJeqcO::getprIeJeOpEJ()
{
    return prIeJeOpEJ;
}

void DispIeqcJeqcO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    DispIeqcJecO::simUpdateAll();
    prIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->prOeOpE;
}
