/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqKeqt.h"
#include "EndFrameq.h"
#include "FullColumn.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqKeqt> DispIeqtJeqKeqt::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqKeqt>(frmi, frmj);
    inst->initialize();
    return inst;
}

FMatDsptr DispIeqtJeqKeqt::getppVectorpEKpt()
{
    return pprIeJeKepEIpt;
}

FColDsptr DispIeqtJeqKeqt::getppVectorptpt()
{
    return pprIeJeKeptpt;
}

void DispIeqtJeqKeqt::preVelIC()
{
    DispIeqJeqKeq::preVelIC();
    calcpVectorpt();
}

void DispIeqtJeqKeqt::preAccIC()
{
    DispIeqJeqKeq::preAccIC();
    calcppVectorpXJpt();
    calcppVectorpEJpt();
    calcppVectorptpt();
}

void DispIeqtJeqKeqt::calcpVectorpt()
{
    // rIeJeKe = aAOKeT * (rOJeO - rOIeO)
    prIeJeKept = eFrmK->getpAOept()->transposeTimesFullColumn(rIeJeO)->minusFullColumn(
        aAOKe->transposeTimesFullColumn(eFrmI->getprOeOpt()));
}

void DispIeqtJeqKeqt::calcppVectorpXIpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXIpt = pAOKeTpt * prIeJeOpXI + aAOKeT * pprIeJeOpXIpt
    // pprIeJeKepXIpt = pAOKeTpt * prIeJeOpXI + aAOKeT * 0
    pprIeJeKepXIpt = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXI());
}

void DispIeqtJeqKeqt::calcppVectorpEIpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEIpt = pAOKeTpt * prIeJeOpEI + aAOKeT * pprIeJeOpEIpt
    auto term2 = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEI());
    auto term3 = eFrmK->aAOe->transposeTimesFullMatrix(dispIeJeO->getppVectorpEIpt());
    pprIeJeKepEIpt = term2->plusFullMatrix(term3);
}

void DispIeqtJeqKeqt::calcppVectorpXJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * pprIeJeOpXJpt
    // pprIeJeKepXJpt = pAOKeTpt * prIeJeOpXJ + aAOKeT * 0
    pprIeJeKepXJpt = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpXJ());
}

void DispIeqtJeqKeqt::calcppVectorpEJpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * pprIeJeOpEJpt
    // pprIeJeKepEJpt = pAOKeTpt * prIeJeOpEJ + aAOKeT * 0
    pprIeJeKepEJpt = eFrmK->getpAOept()->transposeTimesFullMatrix(dispIeJeO->getpVectorpEJ());
}

void DispIeqtJeqKeqt::calcppVectorpEKpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKepEKpt = ppAOKeTpEKpt * rIeJeO + pAOKeTpEK * prIeJeOpt
    auto term1 = eFrmK->ppAOeTpEpttimesFullColumn(rIeJeO);
    auto term2 = eFrmK->pAOeTpEtimesFullColumn(dispIeJeO->getpVectorpt());
    pprIeJeKepEKpt = term1->plusFullMatrix(term2);
}

void DispIeqtJeqKeqt::calcppVectorptpt()
{
    // rIeJeKe = aAOKeT * rIeJeO
    // prIeJeKept = pAOKeTpt * rIeJeO + aAOKeT * prIeJeOpt
    // pprIeJeKeptpt = ppAOKeTptpt * rIeJeO + 2 * pAOKeTpt * prIeJeOpt + aAOKeT * pprIeJeOptpt
    auto term1 = eFrmK->getppAOeptpt()->transposeTimesFullColumn(rIeJeO);
    auto term2 = eFrmK->getpAOept()->transposeTimesFullColumn(dispIeJeO->getpVectorpt())->times(2.0);
    auto term3 = eFrmK->aAOe->transposeTimesFullColumn(dispIeJeO->getppVectorptpt());
    pprIeJeKeptpt = term1->plusFullColumn(term2->plusFullColumn(term3));
}

FColDsptr DispIeqtJeqKeqt::getpVectorpt()
{
    return prIeJeKept;
}

FMatDsptr DispIeqtJeqKeqt::getppVectorpXIpt()
{
    return pprIeJeKepEIpt;
}

FMatDsptr DispIeqtJeqKeqt::getppVectorpEJpt()
{
    return pprIeJeKepEIpt;
}

FMatDsptr DispIeqtJeqKeqt::getppVectorpEIpt()
{
    return pprIeJeKepEIpt;
}
