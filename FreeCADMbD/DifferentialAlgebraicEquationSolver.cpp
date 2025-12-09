/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "DifferentialAlgebraicEquationSolver.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DifferentialAlgebraicEquationSolver> DifferentialAlgebraicEquationSolver::With()
{
    auto inst = std::make_shared<DifferentialAlgebraicEquationSolver>();
    inst->initialize();
    return inst;
}

void DifferentialAlgebraicEquationSolver::run()
{
    throw SimulationStoppingError("To be implemented.");
}

void DifferentialAlgebraicEquationSolver::setSystem(Solver* sys)
{
    throw SimulationStoppingError("To be implemented.");
}

void DifferentialAlgebraicEquationSolver::useDAETrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
    throw SimulationStoppingError("To be implemented.");
}
