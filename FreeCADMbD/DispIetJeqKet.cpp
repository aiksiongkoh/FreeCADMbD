/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIetJeqKet.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIetJeqKet> DispIetJeqKet::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIetJeqKet>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIetJeqKet::simUpdateAll()
{
    DispIeJeqKe::simUpdateAll();
    calcpVectorpt();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorptpt();
}

void MbD::DispIetJeqKet::preVelIC()
{
    DispIeJeqKe::preVelIC();
    calcpVectorpt();
}

void MbD::DispIetJeqKet::preAccIC()
{
    DispIeJeqKe::preAccIC();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorptpt();
}

void MbD::DispIetJeqKet::calcpVectorpt()
{
    // rIeJeKe = aAOKeT * (rOJeO - rOIeO)
    prIeJeKept = frmKe->getpAOept()->transposeTimesFullColumn(rIeJeO)->minusFullColumn(
        aAOKe->transposeTimesFullColumn(frmIe->getprOeOpt()));
}

void MbD::DispIetJeqKet::calcppVectorpXJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * pprIeJeOpXJpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXJ());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpXJpt());
    pprIeJeKepXJpt = term2->plusFullMatrix(term3);
}

void MbD::DispIetJeqKet::calcppVectorpEJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * pprIeJeOpEJpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEJ());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpEJpt());
    pprIeJeKepEJpt = term2->plusFullMatrix(term3);
}

void MbD::DispIetJeqKet::calcppVectorptpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKeptpt = ppAOKeTptpt * rIeJeO + 2 * pAOKeTpt * prIeJeOpt + aAOKeT * pprIeJeOptpt
    auto term1 = frmKe->getppAOeptpt()->transposeTimesFullColumn(rIeJeO);
    auto term2 = frmKe->getpAOept()->transposeTimesFullColumn(dispIeJeO->getpVectorpt())->times(2.0);
    auto term3 = frmKe->aAOe->transposeTimesFullColumn(dispIeJeO->getppVectorptpt());
    pprIeJeKeptpt = term1->plusFullColumn(term2->plusFullColumn(term3));
}
