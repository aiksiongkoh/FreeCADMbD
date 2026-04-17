/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeKeq.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeJeKeq> DispIeJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeJeKeq::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEK();
    calcppVectorpEKpEK();
}

void MbD::DispIeJeKeq::calcpVectorpEK()
{
    // prIeJeKepEK = pAOKeTpEK * rIeJeO
    prIeJeKepEK = frmKe->pAOeTpEtimesFullColumn(rIeJeO);
}

void MbD::DispIeJeKeq::calcppVectorpEKpEK()
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    pprIeJeKepEKpEK = frmKe->ppAOeTpEpEtimesFullColumn(rIeJeO);
}
