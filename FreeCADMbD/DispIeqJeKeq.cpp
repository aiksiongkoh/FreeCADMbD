/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeqJeKeq> DispIeqJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeKeq::simUpdateAll()
{
    DispIeqJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXIpEK();
    calcppVectorpEIpEK();
    calcppVectorpEKpEK();
}

void DispIeqJeKeq::calcpVectorpEK()
{
    // prIeJeKepEK = pAOKeTpEK * rIeJeO
    prIeJeKepEK = eFrmK->pAOeTpEtimesFullColumn(rIeJeO);
}

void DispIeqJeKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = eFrmK->ppAOeTpEpEtimesFullColumn(rIeJeO);
}

void DispIeqJeKeq::calcppVectorpXIpEK()
{
    // pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    pprIeJeKepXIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpXI);
}

void DispIeqJeKeq::calcppVectorpEIpEK()
{
    // pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    pprIeJeKepEIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpEI);
}

FMatDsptr DispIeqJeKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr DispIeqJeKeq::getppVectorpXIpEK()
{
    return pprIeJeKepXIpEK;
}

FMatFColDsptr DispIeqJeKeq::getppVectorpEIpEK()
{
    return pprIeJeKepEIpEK;
}

FMatFColDsptr DispIeqJeKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
