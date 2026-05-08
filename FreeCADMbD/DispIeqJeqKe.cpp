/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeqJeqKe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeqJeqKe> DispIeqJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqJeqKe::calcppVectorpEJpEJ()
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

FMatDsptr DispIeqJeqKe::getpVectorpXJ()
{
    return prIeJeKepXJ;
}

FMatDsptr DispIeqJeqKe::getpVectorpEJ()
{
    return prIeJeKepEJ;
}

FMatFColDsptr DispIeqJeqKe::getppVectorpEJpEJ()
{
    return pprIeJeKepEJpEJ;
}

void DispIeqJeqKe::simUpdateAll()
{
    DispIeqJeKe::simUpdateAll();
    calcpVectorpXJ();
    calcpVectorpEJ();
    calcppVectorpEJpEJ();
}

void DispIeqJeqKe::calcpVectorpXJ()
{
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    prIeJeKepXJ = eFrmK->aAOe->transposeTimesFullMatrix(prIeJeOpXJ);
}

void DispIeqJeqKe::calcpVectorpEJ()
{
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    prIeJeKepEJ = eFrmK->aAOe->transposeTimesFullMatrix(prIeJeOpEJ);
}

FMatDsptr DispIeqJeqKe::getppCompipEJpEJ(size_t axis)
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
