/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <iostream>
#include <limits>
#include <memory>
#include <chrono>

#include "MatrixSolver.h"
#include "SparseMatrix.h"
#include "FullMatrix.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MatrixSolver> MatrixSolver::With()
{
    auto inst = std::make_shared<MatrixSolver>();
    inst->initialize();
    return inst;
}

void MatrixSolver::initialize()
{
    Solver::initialize();
    singularPivotTolerance = 4 * std::numeric_limits<double>::epsilon();
}

void MatrixSolver::run()
{
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::setSystem(Solver*)
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr MatrixSolver::solvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    timedSolvewithsaveOriginal(spMat, fullCol, saveOriginal);
    return answerX;
}

FColDsptr MatrixSolver::solvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
    timedSolvewithsaveOriginal(fullMat, fullCol, saveOriginal);
    return answerX;
}

FColDsptr MatrixSolver::timedSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    auto start = std::chrono::steady_clock::now();

    basicSolvewithsaveOriginal(spMat, fullCol, saveOriginal);

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    millisecondsToRun = std::chrono::duration<double, std::milli>(diff).count();
    //std::cout << "milliseconds to run = " << millisecondsToRun << std::endl;
    return answerX;
}

FColDsptr MatrixSolver::timedSolvewithsaveOriginal(FMatDsptr, FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr MatrixSolver::basicSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr MatrixSolver::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void MatrixSolver::preSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::doPivoting(size_t p)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::forwardEliminateWithPivot(size_t p)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::backSubstituteIntoDU()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::postSolve()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void MatrixSolver::findScalingsForRowRange(size_t begin, size_t end)
{
    //"Row element * scaling <= 1.0."
    rowScalings = std::make_shared<FullColumn<double>>(m);
    for (size_t i = begin; i < end; i++)
    {
        double maxRowMagnitude = getmatrixArowimaxMagnitude(i);
        if (maxRowMagnitude == 0.0) throwSingularMatrixError("");
        rowScalings->at(i) = 1.0 / maxRowMagnitude;
    }
}

double MatrixSolver::getmatrixArowimaxMagnitude(size_t i)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

void MatrixSolver::throwSingularMatrixError(const std::string& str)
{
    throw SingularMatrixError(str);
}

void MatrixSolver::throwSingularMatrixError(const std::string& str, std::shared_ptr<FullColumn<size_t>> redunEqnNos)
{
    throw SingularMatrixError(str, redunEqnNos);
}
