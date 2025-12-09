/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "VelSolver.h"
#include "MatrixSolver.h"
#include "SystemSolver.h"
#include "GESpMatParPvPrecise.h"
#include "SingularMatrixError.h"
#include "GESpMatParPvMarko.h"
#include "GESpMatParPvMarkoFast.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelSolver> VelSolver::With()
{
    auto inst = std::make_shared<VelSolver>();
    inst->initialize();
    return inst;
}

void VelSolver::run()
{
    throw SimulationStoppingError("To be implemented.");
}

void VelSolver::basicSolveEquations()
{
    x = matrixSolver->solvewithsaveOriginal(jacobian, errorVector, true);
}

void VelSolver::handleSingularMatrix()
{
    auto& r = *matrixSolver;
    std::string str = typeid(r).name();
    if (str.find("GESpMatParPvMarkoFast") != std::string::npos) {
        matrixSolver = GESpMatParPvPrecise::With();
        solveEquations();
    }
    else {
        str = typeid(r).name();
        if (str.find("GESpMatParPvPrecise") != std::string::npos) {
            logSingularMatrixMessage();
            matrixSolver = matrixSolverClassNew();
        }
        else {
            throw SimulationStoppingError("To be implemented.");
        }
    }
}

void VelSolver::logSingularMatrixMessage()
{
    std::string str = "MbD: Velocity solver has encountered a singular matrix.";
    system->logString(str);
}

std::shared_ptr<MatrixSolver> VelSolver::matrixSolverClassNew()
{
    return GESpMatParPvPrecise::With();
}

void VelSolver::solveEquations()
{
    try {
        basicSolveEquations();
    }
    catch (SingularMatrixError ex) {
        handleSingularMatrix();
    }
}

void VelSolver::setSystem(Solver* sys)
{
    system = static_cast<SystemSolver*>(sys);
}
