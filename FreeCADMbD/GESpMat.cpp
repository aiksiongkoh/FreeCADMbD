/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <iostream>
 
#include "GESpMat.h"
#include "FullColumn.h"
#include "SparseMatrix.h"
#include "SimulationStoppingError.h"

using namespace MbD;

FColDsptr GESpMat::solvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    timedSolvewithsaveOriginal(spMat, fullCol, saveOriginal);
    return answerX;
}

FColDsptr GESpMat::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    auto debug = false;
    if (debug) {
        spMat->outputCSV("../debugcpp.csv");
        fullCol->appendCSV("../debugcpp.csv");
    }
    preSolvewithsaveOriginal(spMat, fullCol, saveOriginal);
    if (debug) {
        matrixA->appendCSV("../debugcpp.csv");
    }
    for (size_t p = 0; p < m; p++)
    {
        doPivoting(p);
        forwardEliminateWithPivot(p);
    }
    backSubstituteIntoDU();
    postSolve();
    if (debug) {
        answerX->appendCSV("../debugcpp.csv");
    }
    return answerX;
}

FColDsptr GESpMat::basicSolvewithsaveOriginal(FMatDsptr, FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void GESpMat::preSolvewithsaveOriginal(FMatDsptr, FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
}

void GESpMat::preSolvewithsaveOriginal(SpMatDsptr, FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
}

double GESpMat::getmatrixArowimaxMagnitude(size_t i)
{
    return matrixA->at(i)->maxMagnitude();
}
