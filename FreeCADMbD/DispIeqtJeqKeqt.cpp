/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqKeqt.h"
#include "EndFrameqc.h"
#include "FullColumn.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqKeqt> DispIeqtJeqKeqt::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqKeqt>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeqtJeqKeqt::simUpdateAll()
{
    DispIeqJeqKeq::simUpdateAll();
    calcpVectorpt();
    calcppVectorpXIpt();
    calcppVectorpEIpt();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorpEKpt();
    calcppVectorptpt();
}

void MbD::DispIeqtJeqKeqt::preVelIC()
{
    DispIeqJeqKeq::preVelIC();
    calcpVectorpt();
}

void MbD::DispIeqtJeqKeqt::preAccIC()
{
    DispIeqJeqKeq::preAccIC();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorptpt();
}

void MbD::DispIeqtJeqKeqt::calcpVectorpt()
{
    // rIeJeKe = aAOKeT * (rOJeO - rOIeO)
    prIeJeKept = frmKe->getpAOept()->transposeTimesFullColumn(rIeJeO)->minusFullColumn(
        aAOKe->transposeTimesFullColumn(frmIe->getprOeOpt()));
}

void MbD::DispIeqtJeqKeqt::calcppVectorpXIpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXIpt = pAOKeTpt * prIeJeOpXI + aAOKeT * pprIeJeOpXIpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXI());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpXIpt());
    pprIeJeKepXIpt = term2->plusFullMatrix(term3);
}

void MbD::DispIeqtJeqKeqt::calcppVectorpEIpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEIpt = pAOKeTpt * prIeJeOpEI + aAOKeT * pprIeJeOpEIpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEI());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpEIpt());
    pprIeJeKepEIpt = term2->plusFullMatrix(term3);
}

void MbD::DispIeqtJeqKeqt::calcppVectorpXJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * pprIeJeOpXJpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXJ());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpXJpt());
    pprIeJeKepXJpt = term2->plusFullMatrix(term3);
}

void MbD::DispIeqtJeqKeqt::calcppVectorpEJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * pprIeJeOpEJpt
    auto term2 = frmKe->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEJ());
    auto term3 = frmKe->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpEJpt());
    pprIeJeKepEJpt = term2->plusFullMatrix(term3);
}

void MbD::DispIeqtJeqKeqt::calcppVectorpEKpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEKpt = ppAOKeTpEKpt * rIeJeO + pAOKeTpEK * prIeJeOpt
    auto term1 = frmKe->ppAOeTpEpttimesFullColumn(rIeJeO);
    auto term2 = frmKe->pAOeTpEtimesFullColumn(dispIeJeO->getpVectorpt());
    pprIeJeKepEKpt = term1->plusFullMatrix(term2);
}

void MbD::DispIeqtJeqKeqt::calcppVectorptpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKeptpt = ppAOKeTptpt * rIeJeO + 2 * pAOKeTpt * prIeJeOpt + aAOKeT * pprIeJeOptpt
    auto term1 = frmKe->getppAOeptpt()->transposeTimesFullColumn(rIeJeO);
    auto term2 = frmKe->getpAOept()->transposeTimesFullColumn(dispIeJeO->getpVectorpt())->times(2.0);
    auto term3 = frmKe->aAOe->transposeTimesFullColumn(dispIeJeO->getppVectorptpt());
    pprIeJeKeptpt = term1->plusFullColumn(term2->plusFullColumn(term3));
}
