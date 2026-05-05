/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeKeq> DispIeqJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeqJeKeq::simUpdateAll()
{
    DispIeqJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXIpEK();
    calcppVectorpEIpEK();
    calcppVectorpEKpEK();
}

void MbD::DispIeqJeKeq::calcpVectorpEK()
{
    // prIeJeKepEK = pAOKeTpEK * rIeJeO
    prIeJeKepEK = eFrmK->pAOeTpEtimesFullColumn(rIeJeO);
}

void MbD::DispIeqJeKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = eFrmK->ppAOeTpEpEtimesFullColumn(rIeJeO);
}

void MbD::DispIeqJeKeq::calcppVectorpXIpEK()
{
    // pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    pprIeJeKepXIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpXI);
}

void MbD::DispIeqJeKeq::calcppVectorpEIpEK()
{
    // pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    pprIeJeKepEIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpEI);
}

FMatDsptr MbD::DispIeqJeKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr MbD::DispIeqJeKeq::getppVectorpXIpEK()
{
    return pprIeJeKepXIpEK;
}

FMatFColDsptr MbD::DispIeqJeKeq::getppVectorpEIpEK()
{
    return pprIeJeKepEIpEK;
}

FMatFColDsptr MbD::DispIeqJeKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
