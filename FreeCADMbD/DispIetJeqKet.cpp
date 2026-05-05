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

FColDsptr MbD::DispIetJeqKet::getppVectorptpt()
{
    return pprIeJeKeptpt;
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
    prIeJeKept = eFrmK->getpAOept()->transposeTimesFullColumn(rIeJeO)->minusFullColumn(
        aAOKe->transposeTimesFullColumn(eFrmI->getprOeOpt()));
}

void MbD::DispIetJeqKet::calcppVectorpXJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * pprIeJeOpXJpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * 0
    pprIeJeKepXJpt = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXJ());
}

void MbD::DispIetJeqKet::calcppVectorpEJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * pprIeJeOpEJpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * 0
    pprIeJeKepEJpt = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEJ());
}

void MbD::DispIetJeqKet::calcppVectorptpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKeptpt = ppAOKeTptpt * rIeJeO + 2 * pAOKeTpt * prIeJeOpt + aAOKeT * pprIeJeOptpt
    auto term1 = eFrmK->getppAOeptpt()->transposeTimesFullColumn(rIeJeO);
    auto term2 = eFrmK->getpAOept()->transposeTimesFullColumn(dispIeJeO->getpVectorpt())->times(2.0);
    auto term3 = eFrmK->aAOe->transposeTimesFullColumn(dispIeJeO->getppVectorptpt());
    pprIeJeKeptpt = term1->plusFullColumn(term2->plusFullColumn(term3));
}

FColDsptr MbD::DispIetJeqKet::getpVectorpt()
{
    return prIeJeKept;
}

FMatDsptr MbD::DispIetJeqKet::getppVectorpXJpt()
{
    return pprIeJeKepXJpt;
}

FMatDsptr MbD::DispIetJeqKet::getppVectorpEJpt()
{
    return pprIeJeKepEJpt;
}
