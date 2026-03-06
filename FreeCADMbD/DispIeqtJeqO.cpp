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
    pprIeJeOpEIpEI = std::static_pointer_cast<EndFrameqct>(frmIe)->pprOeOpEpE->negated();
}

void MbD::DispIeqtJeqO::preVelIC()
{
    DispIeqJeqO::preVelIC();
    calcpvaluept();
}

void MbD::DispIeqtJeqO::preAccIC()
{
    DispIeqJeqO::preAccIC();
    calcppvaluepEIpt();
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

FMatDsptr MbD::DispIeqtJeqO::getpprIeJeOpEIpt()
{
    return pprIeJeOpEIpt;
}

FColDsptr MbD::DispIeqtJeqO::getpprIeJeOptpt()
{
    return pprIeJeOptpt;
}

void DispIeqtJeqO::calcpvaluept()
{
    prIeJeOpt = std::dynamic_pointer_cast<EndFrameqct>(frmIe)->prOeOpt->negated();
}

void DispIeqtJeqO::calcppvalueptpt()
{
    pprIeJeOptpt = std::dynamic_pointer_cast<EndFrameqct>(frmIe)->pprOeOptpt->negated();
}

void DispIeqtJeqO::calcppvaluepEIpt()
{
    pprIeJeOpEIpt = std::dynamic_pointer_cast<EndFrameqct>(frmIe)->pprOeOpEpt->negated();
}
