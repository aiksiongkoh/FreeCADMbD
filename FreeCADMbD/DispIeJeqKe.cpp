/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqKe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeJeqKe> DispIeJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::DispIeJeqKe::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpEJ();
    calcppVectorpEJpEJ();
}

void MbD::DispIeJeqKe::calcpVectorpXJ()
{
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    prIeJeKepXJ = frmKe->aAOe->transposeTimesFullMatrix(prIeJeOpXJ);
}

void MbD::DispIeJeqKe::calcpVectorpEJ()
{
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    prIeJeKepEJ = frmKe->aAOe->transposeTimesFullMatrix(prIeJeOpEJ);
}

void MbD::DispIeJeqKe::calcppVectorpEJpEJ()
{
    //pprIeJeKepEJpEJ = aAOKeT * pprIeJeOpEJpEJ
    auto pprIeJeOpEJpEJ = dispIeJeO->getppVectorpEJpEJ();
    pprIeJeKepEJpEJ = FullMatrix<FColDsptr>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            pprIeJeKepEJpEJ->atijput(i, j, aAOKe->transposeTimesFullColumn(pprIeJeOpEJpEJ->at(i)->at(j)));
        }
    }
}

FMatDsptr MbD::DispIeJeqKe::getprIeJeKepXJ()
{
    return prIeJeKepXJ;
}

FMatDsptr MbD::DispIeJeqKe::getprIeJeKepEJ()
{
    return prIeJeKepEJ;
}

FMatDsptr MbD::DispIeJeqKe::getppriIeJeKepEJpEJ(size_t axis)
{
    auto answer = FullMatrix<double>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pprIeJeKepEipE = pprIeJeKepEJpEJ->at(i);
        for (size_t j = 0; j < 4; j++) {
            answeri->at(j) = pprIeJeKepEipE->at(j)->at(axis);
        }
    }
    return answer;
}
