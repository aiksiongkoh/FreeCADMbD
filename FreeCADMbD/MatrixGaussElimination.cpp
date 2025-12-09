/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MatrixGaussElimination.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MatrixGaussElimination> MatrixGaussElimination::With()
{
    auto inst = std::make_shared<MatrixGaussElimination>();
    inst->initialize();
    return inst;
}

void MatrixGaussElimination::forwardEliminateWithPivot(size_t p)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}
