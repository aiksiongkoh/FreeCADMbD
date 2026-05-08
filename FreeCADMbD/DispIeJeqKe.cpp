/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeJeqKe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DispIeJeqKe> DispIeJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeJeqKe::simUpdateAll()
{
    DispIeJeKe::simUpdateAll();
    calcpVectorpXJ();
    calcpVectorpEJ();
    calcppVectorpEJpEJ();
}

void DispIeJeqKe::calcpVectorpXJ()
{
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    auto prIeJeOpXJ = dispIeJeO->getpVectorpXJ();
    prIeJeKepXJ = eFrmK->aAOe->transposeTimesFullMatrix(prIeJeOpXJ);
}

void DispIeJeqKe::calcpVectorpEJ()
{
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    auto prIeJeOpEJ = dispIeJeO->getpVectorpEJ();
    prIeJeKepEJ = eFrmK->aAOe->transposeTimesFullMatrix(prIeJeOpEJ);
}

void DispIeJeqKe::calcppVectorpEJpEJ()
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

FMatDsptr DispIeJeqKe::getpVectorpXJ()
{
    return prIeJeKepXJ;
}

FMatDsptr DispIeJeqKe::getpVectorpEJ()
{
    return prIeJeKepEJ;
}

FMatFColDsptr DispIeJeqKe::getppVectorpEJpEJ()
{
    return pprIeJeKepEJpEJ;
}

FMatDsptr DispIeJeqKe::getppCompipEJpEJ(size_t axis)
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
