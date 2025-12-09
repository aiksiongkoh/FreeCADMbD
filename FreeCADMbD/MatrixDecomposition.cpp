/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MatrixDecomposition.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MatrixDecomposition> MatrixDecomposition::With()
{
    auto inst = std::make_shared<MatrixDecomposition>();
    inst->initialize();
    return inst;
}

FColDsptr MatrixDecomposition::forAndBackSubsaveOriginal(FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void MatrixDecomposition::applyRowOrderOnRightHandSideB()
{
    FColDsptr answer = std::make_shared<FullColumn<double>>(m);
    for (size_t i = 0; i < m; i++)
    {
        answer->at(i) = rightHandSideB->at(rowOrder->at(i));
    }
    rightHandSideB = answer;
}

FColDsptr MatrixDecomposition::basicSolvewithsaveOriginal(FMatDsptr, FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void MatrixDecomposition::forwardSubstituteIntoL()
{
    throw SimulationStoppingError("To be implemented.");
}

void MatrixDecomposition::backSubstituteIntoU()
{
    throw SimulationStoppingError("To be implemented.");
}

void MatrixDecomposition::forwardSubstituteIntoLD()
{
    throw SimulationStoppingError("To be implemented.");
}

void MatrixDecomposition::postSolve()
{
    throw SimulationStoppingError("To be implemented.");
}

void MatrixDecomposition::preSolvesaveOriginal(FMatDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
}
