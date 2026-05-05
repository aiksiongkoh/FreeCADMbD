/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqO.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqO> DispIeqtJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeqtJeqO::simUpdateAll()
{
    //rIeJeO = rOJeO(q,t) - rOIeO(q)
    //rIeJeO = rOJpO + aAOJp * rJpJeJp - (rOIpO + aAOIp * rIpIeIp(t))
    //prIeJeOpXI = -[I]
    //prIeJeOpEI = -pAOIppEI * rIpIeIp(t)       Not a constant
    //prIeJeOpXJ = [I]
    //prIeJeOpEJ = pAOJppEJ * rJpJeJp       Not a constant
    //pprIeJeOpEIpEI = -ppAOIppEIpEI * rIpIeIp(t)       Not a constant
    //pprIeJeOpEJpEJ = ppAOJppEJpEJ * rJpJeJp   =    Constant * Constant

    DispIeqJeqO::simUpdateAll();
    calcppVectorpEIpEI();   //No longer a constant
}

void MbD::DispIeqtJeqO::preVelIC()
{
    DispIeqJeqO::preVelIC();
    calcpVectorpt();
}

void MbD::DispIeqtJeqO::preAccIC()
{
    DispIeqJeqO::preAccIC();
    calcppVectorpEIpt();
    calcppVectorptpt();
}

FColDsptr MbD::DispIeqtJeqO::getpVectorpt()
{
    return prIeJeOpt;
}

FMatDsptr MbD::DispIeqtJeqO::getppVectorpEIpt()
{
    return pprIeJeOpEIpt;
}

FColDsptr MbD::DispIeqtJeqO::getppVectorptpt()
{
    return pprIeJeOptpt;
}

void DispIeqtJeqO::calcpVectorpt()
{
    prIeJeOpt = eFrmI->getprOeOpt()->negated();
}

void DispIeqtJeqO::calcppVectorptpt()
{
    // pprIeJeOptpt = std::dynamic_pointer_cast<EndFramect>(frmIe)->pprOeOptpt->negated();
    pprIeJeOptpt = eFrmI->getpprOeOptpt()->negated();
}

void DispIeqtJeqO::calcppVectorpEIpt()
{
    // pprIeJeOpEIpt = std::dynamic_pointer_cast<EndFrameqct>(frmIe)->pprOeOpEpt->negated();
    pprIeJeOpEIpt = eFrmI->getpprOeOpEpt()->negated();
}
