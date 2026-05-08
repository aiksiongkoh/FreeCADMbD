/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeJeqKeq> DispIeJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeJeqKeq::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpXJpEK();
    calcppVectorpEJpEK();
    calcppVectorpEKpEK();
}

void DispIeJeqKeq::calcppVectorpXJpEK()
{
    // pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    pprIeJeKepXJpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpXJ);
}

void DispIeJeqKeq::calcppVectorpEJpEK()
{
    // pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    pprIeJeKepEJpEK = eFrmK->pAOeTpEtimesFullMatrix(prIeJeOpEJ);
}

FMatDsptr DispIeJeqKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr DispIeJeqKeq::getppVectorpXJpEK()
{
    return pprIeJeKepXJpEK;
}

FMatFColDsptr DispIeJeqKeq::getppVectorpEJpEK()
{
    return pprIeJeKepEJpEK;
}

FMatFColDsptr DispIeJeqKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
