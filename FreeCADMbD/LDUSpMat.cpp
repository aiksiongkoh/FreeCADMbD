/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "LDUSpMat.h"
#include "FullColumn.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<LDUSpMat> LDUSpMat::With()
{
    auto inst = std::make_shared<LDUSpMat>();
    inst->initialize();
    return inst;
}

FColDsptr LDUSpMat::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    decomposesaveOriginal(spMat, saveOriginal);
    FColDsptr answer = forAndBackSubsaveOriginal(fullCol, saveOriginal);
    return answer;
}

void LDUSpMat::decomposesaveOriginal(FMatDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
}

void LDUSpMat::decomposesaveOriginal(SpMatDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr LDUSpMat::forAndBackSubsaveOriginal(FColDsptr, bool)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

double LDUSpMat::getmatrixArowimaxMagnitude(size_t i)
{
    return matrixA->at(i)->maxMagnitude();
}

void LDUSpMat::forwardSubstituteIntoL()
{
    //"L is lower triangular with nonzero and ones in diagonal."
    auto vectorc = std::make_shared<FullColumn<double>>(n);
    vectorc->at(0) = rightHandSideB->at(0);
    for (size_t i = 1; i < n; i++)
    {
        auto& rowi = matrixA->at(i);
        double sum = 0.0;
        for (auto const& keyValue : *rowi) {
            size_t j = keyValue.first;
            double duij = keyValue.second;
            sum += duij * vectorc->at(j);
        }
        vectorc->at(i) = rightHandSideB->at(i) - sum;
    }
    rightHandSideB = vectorc;
}

void LDUSpMat::backSubstituteIntoDU()
{
    //"DU is upper triangular with nonzero diagonals."

    double sum, duij;
    for (size_t i = 0; i < m; i++)
    {
        rightHandSideB->at(i) = rightHandSideB->at(i) / matrixD->at(i);
    }
    answerX = std::make_shared<FullColumn<double>>(m);
    answerX->at(n - 1) = rightHandSideB->at(m - 1);
    for (int i = (int)n - 2; i >= 0; i--)    //Use int because of decrement
    {
        auto& rowi = matrixU->at(i);
        sum = 0.0;
        for (auto const& keyValue : *rowi) {
            auto j = keyValue.first;
            duij = keyValue.second;
            sum += answerX->at(j) * duij;
        }
        answerX->at(i) = rightHandSideB->at(i) - sum;
    }
}
