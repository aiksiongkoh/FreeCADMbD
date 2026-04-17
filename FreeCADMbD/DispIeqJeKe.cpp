/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqJeKe> DispIeqJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeqJeKe::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEI();
    calcppVectorpEIpEI();
}

void MbD::DispIeqJeKe::calcpVectorpXI()
{
    //prIeJeKepXI = aAOKeT * prIeJeOpXI
    auto prIeJeOpXI = dispIeJeO->getpVectorpXI();
    prIeJeKepXI = frmKe->aAOe->transposeTimesFullMatrix(prIeJeOpXI);
}

void MbD::DispIeqJeKe::calcpVectorpEI()
{
    //prIeJeKepEI = aAOKeT * prIeJeOpEI
    auto prIeJeOpEI = dispIeJeO->getpVectorpEI();
    prIeJeKepEI = frmKe->aAOe->transposeTimesFullMatrix(prIeJeOpEI);
}

void MbD::DispIeqJeKe::calcppVectorpEIpEI()
{
    //pprIeJeKepEIpEI = aAOKeT * pprIeJeOpEIpEI
    auto pprIeJeOpEIpEI = dispIeJeO->getppVectorpEIpEI();
    pprIeJeKepEIpEI = FullMatrix<FColDsptr>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            pprIeJeKepEIpEI->atijput(i, j, aAOKe->transposeTimesFullColumn(pprIeJeOpEIpEI->at(i)->at(j)));
        }
    }
}

FMatDsptr MbD::DispIeqJeKe::getprIeJeKepXI()
{
    return prIeJeKepXI;
}

FMatDsptr MbD::DispIeqJeKe::getprIeJeKepEI()
{
    return prIeJeKepEI;
}

FMatDsptr MbD::DispIeqJeKe::getppriIeJeKepEIpEI(size_t axis)
{
    auto answer = FullMatrix<double>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pprIeJeKepEipE = pprIeJeKepEIpEI->at(i);
        for (size_t j = 0; j < 4; j++) {
            answeri->at(j) = pprIeJeKepEipE->at(j)->at(axis);
        }
    }
    return answer;
}
