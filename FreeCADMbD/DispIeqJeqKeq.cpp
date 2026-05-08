/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeqKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqKeq> DispIeqJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeqKeq::simUpdateAll()
{
    DispIeqJeqKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXIpEK();
    calcppVectorpEIpEK();
    calcppVectorpXJpEK();
    calcppVectorpEJpEK();
    calcppVectorpEKpEK();
}

void DispIeqJeqKeq::calcpVectorpEK()
{
    prIeJeKepEK = eFrmK->pAOeTpEtimesFullColumn(rIeJeO);
}

void DispIeqJeqKeq::calcppVectorpXIpEK()
{
    // pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    pprIeJeKepXIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpXI);
}

void DispIeqJeqKeq::calcppVectorpEIpEK()
{
    // pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    pprIeJeKepEIpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpEI);
}

void DispIeqJeqKeq::calcppVectorpXJpEK()
{
    // pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    pprIeJeKepXJpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpXJ);
}

void DispIeqJeqKeq::calcppVectorpEJpEK()
{
    // pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    pprIeJeKepEJpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpEJ);
}

void DispIeqJeqKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = eFrmK->ppAOeTpEpEtimesFullColumn(rIeJeO);
}

FMatDsptr DispIeqJeqKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr DispIeqJeqKeq::getppVectorpXIpEK()
{
    return pprIeJeKepXIpEK;
}

FMatFColDsptr DispIeqJeqKeq::getppVectorpEIpEK()
{
    return pprIeJeKepEIpEK;
}

FMatFColDsptr DispIeqJeqKeq::getppVectorpXJpEK()
{
    return pprIeJeKepXJpEK;
}

FMatFColDsptr DispIeqJeqKeq::getppVectorpEJpEK()
{
    return pprIeJeKepEJpEK;
}

FMatFColDsptr DispIeqJeqKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
