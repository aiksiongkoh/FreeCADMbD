/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>
#include <memory>

#include "QuasiStaticIntegrator.h"
#include "SystemSolver.h"

using namespace MbD;

std::shared_ptr<QuasiStaticIntegrator> QuasiStaticIntegrator::With()
{
    auto inst = std::make_shared<QuasiStaticIntegrator>();
    inst->initialize();
    return inst;
}

void MbD::QuasiStaticIntegrator::runInitialConditionTypeSolution()
{
    system->runStaticIC();
}

void QuasiStaticIntegrator::useTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
    system->useDynTrialStepStats(stats);
}
