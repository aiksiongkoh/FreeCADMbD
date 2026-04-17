/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeJeqKeq> DispIeJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeJeqKeq::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXJpEK();
    calcppVectorpEJpEK();
    calcppVectorpEKpEK();
}

void MbD::DispIeJeqKeq::calcppVectorpXJpEK()
{
    // pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    pprIeJeKepXJpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpXJ);
}

void MbD::DispIeJeqKeq::calcppVectorpEJpEK()
{
    // pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    pprIeJeKepEJpEK = frmKe->pAOeTpEtimesFullMatrix(prIeJeOpEJ);
}
