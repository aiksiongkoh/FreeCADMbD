/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ICKineIntegrator.h"
#include "SystemSolver.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void ICKineIntegrator::runInitialConditionTypeSolution()
{
    system->runPosICKine();
    system->runVelICKine();
    system->runAccICKine();
}

void ICKineIntegrator::iStep(size_t)
{
    throw SimulationStoppingError("To be implemented.");
}

void ICKineIntegrator::selectOrder()
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ICKineIntegrator> ICKineIntegrator::With()
{
    auto inst = std::make_shared<ICKineIntegrator>();
    inst->initialize();
    return inst;
}

void ICKineIntegrator::preRun()
{
    system->logString("MbD: Starting quasi kinematic analysis.");
    QuasiIntegrator::preRun();
}

void ICKineIntegrator::firstStep()
{
    throw SimulationStoppingError("To be implemented.");
}

void ICKineIntegrator::subsequentSteps()
{
    throw SimulationStoppingError("To be implemented.");
}

void ICKineIntegrator::nextStep()
{
    throw SimulationStoppingError("To be implemented.");
}
