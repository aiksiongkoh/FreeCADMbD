/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeJeKeq> DispIeJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeJeKeq::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpEKpEK();
}

void DispIeJeKeq::calcpVectorpEK()
{
    // prIeJeKepEK = pAOKeTpEK * rIeJeO
    prIeJeKepEK = eFrmK->pAOeTpEtimesFullColumn(rIeJeO);
}

void DispIeJeKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = eFrmK->ppAOeTpEpEtimesFullColumn(rIeJeO);
}

FMatDsptr DispIeJeKeq::getpVectorpEK()
{
    return prIeJeKepEK;
}

FMatFColDsptr DispIeJeKeq::getppVectorpEKpEK()
{
    return pprIeJeKepEKpEK;
}
