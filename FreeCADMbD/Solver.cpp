/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <assert.h>

#include "Solver.h"
#include <string>
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<Solver> Solver::With()
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::initialize()
{
    //Do nothing.
}

void Solver::noop()
{
    //No Operations
}

void Solver::initializeLocally()
{
    //Do nothing.
}

void Solver::initializeGlobally()
{
    //Do nothing.
}

void Solver::assignEquationNumbers()
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::preRun()
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::finalize()
{
    //Do nothing.
}

void Solver::reportStats()
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::postRun()
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::logString(const std::string& str)
{
    throw SimulationStoppingError("To be implemented.");
}

void Solver::setSystem(Solver*)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void Solver::handleSingularMatrix()
{
    throw SimulationStoppingError("To be implemented.");
}
