/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqcJecO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqcJecO> DispIeqcJecO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqcJecO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqcJecO::initializeGlobally()
{
    DispIecJecO::initializeGlobally();
    //Variables are constants.
    prIeJeOpXI = FullMatrix<double>::identitysptr(3)->negated();
    pprIeJeOpEIpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->pprOeOpEpE->negated();
}

FMatDsptr MbD::DispIeqcJecO::getprIeJeOpXI()
{
    return prIeJeOpXI;
}

FMatDsptr MbD::DispIeqcJecO::getprIeJeOpEI()
{
    return prIeJeOpEI;
}

void DispIeqcJecO::calcPostDynCorrectorIteration()
{
    //rIeJeO = rOJeO - rOIeO
    DispIecJecO::calcPostDynCorrectorIteration();
    prIeJeOpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->prOeOpE->negated();
}
