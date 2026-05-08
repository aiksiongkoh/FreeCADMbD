/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqO.h"
#include "EndFrameq.h"
#include "EndFrameqt.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqO> DispIeqtJeqO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqO>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqtJeqO::simUpdateAll()
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

void DispIeqtJeqO::preVelIC()
{
    DispIeqJeqO::preVelIC();
    calcpVectorpt();
}

void DispIeqtJeqO::preAccIC()
{
    DispIeqJeqO::preAccIC();
    calcppVectorpEIpt();
    calcppVectorptpt();
}

FColDsptr DispIeqtJeqO::getpVectorpt()
{
    return prIeJeOpt;
}

FMatDsptr DispIeqtJeqO::getppVectorpEIpt()
{
    return pprIeJeOpEIpt;
}

FColDsptr DispIeqtJeqO::getppVectorptpt()
{
    return pprIeJeOptpt;
}

void DispIeqtJeqO::calcpVectorpt()
{
    prIeJeOpt = eFrmI->getprOeOpt()->negated();
}

void DispIeqtJeqO::calcppVectorptpt()
{
    // pprIeJeOptpt = std::dynamic_pointer_cast<EndFramet>(frmIe)->pprOeOptpt->negated();
    pprIeJeOptpt = eFrmI->getpprOeOptpt()->negated();
}

void DispIeqtJeqO::calcppVectorpEIpt()
{
    // pprIeJeOpEIpt = std::dynamic_pointer_cast<EndFrameqt>(frmIe)->pprOeOpEpt->negated();
    pprIeJeOpEIpt = eFrmI->getpprOeOpEpt()->negated();
}
