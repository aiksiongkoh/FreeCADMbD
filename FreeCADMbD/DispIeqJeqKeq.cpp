/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqJeqKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqKeq> DispIeqJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeqJeqKeq::simUpdateAll()
{
    DispIeqJeqKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXIpEK();
    calcppVectorpEIpEK();
    calcppVectorpXJpEK();
    calcppVectorpEJpEK();
    calcppVectorpEKpEK();
}

void MbD::DispIeqJeqKeq::calcpVectorpEK()
{
    prIeJeKepEK = frmKe->pAOeTpEtimesFullColumn(rIeJeO);
}

void MbD::DispIeqJeqKeq::calcppVectorpXIpEK()
{
    // pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    pprIeJeKepXIpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpXI);
}

void MbD::DispIeqJeqKeq::calcppVectorpEIpEK()
{
    // pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    pprIeJeKepEIpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpEI);
}

void MbD::DispIeqJeqKeq::calcppVectorpXJpEK()
{
    // pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    pprIeJeKepXJpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpXJ);
}

void MbD::DispIeqJeqKeq::calcppVectorpEJpEK()
{
    // pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    pprIeJeKepEJpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpEJ);
}

void MbD::DispIeqJeqKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = frmKe->ppAOeTpEpEtimesFullColumn(rIeJeO);
}

FMatDsptr MbD::DispIeqJeqKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr MbD::DispIeqJeqKeq::getppVectorpXIpEK()
{
    return pprIeJeKepXIpEK;
}

FMatFColDsptr MbD::DispIeqJeqKeq::getppVectorpEIpEK()
{
    return pprIeJeKepEIpEK;
}

FMatFColDsptr MbD::DispIeqJeqKeq::getppVectorpXJpEK()
{
    return pprIeJeKepXJpEK;
}

FMatFColDsptr MbD::DispIeqJeqKeq::getppVectorpEJpEK()
{
    return pprIeJeKepEJpEK;
}

FMatFColDsptr MbD::DispIeqJeqKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
