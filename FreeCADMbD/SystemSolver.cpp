/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <vector>
#include <set>
#include <algorithm>

#include "SystemSolver.h"
#include "System.h"
#include "NewtonRaphson.h"
#include "PosICNewtonRaphson.h"
#include "RedundantConstraint.h"
#include "NotKinematicError.h"
#include "ICKineIntegrator.h"
#include "KineIntegrator.h"
#include "DiscontinuityError.h"
#include "PosICKineNewtonRaphson.h"
#include "PosKineNewtonRaphson.h"
#include "VelICSolver.h"
#include "AccICNewtonRaphson.h"
#include "VelKineSolver.h"
#include "AccKineNewtonRaphson.h"
#include "VelICKineSolver.h"
#include "AccICKineNewtonRaphson.h"
#include "DynIntegrator.h"
#include "PosICDragNewtonRaphson.h"
#include "PosICDragLimitNewtonRaphson.h"
#include "SimulationStoppingError.h"

using namespace MbD;


std::shared_ptr<SystemSolver> SystemSolver::With()
{
    auto inst = std::make_shared<SystemSolver>();
    inst->initialize();
    return inst;
}

void SystemSolver::initialize()
{
    tstartPasts = std::make_shared<std::vector<double>>();
}

void SystemSolver::run()
{
    throw SimulationStoppingError("To be implemented.");
}

void SystemSolver::setSystem(Solver*)
{
    //Do not use
    throw SimulationStoppingError("To be implemented.");
}

void SystemSolver::initializeLocally()
{
    setsOfRedundantConstraints = std::make_shared<std::vector<std::shared_ptr<std::set<std::string>>>>();
    direction = (tstart < tend) ? 1.0 : -1.0;
    toutFirst = tstart + (direction * hout);
}

void SystemSolver::initializeGlobally()
{
    //Do nothing.
}

void SystemSolver::runAllIC()
{
    while (true)
    {
        initializeLocally();
        initializeGlobally();
        runPosIC();
        while (needToRedoPosIC())
        {
            runPosIC();
        }
        runVelIC();
        runAccIC();
        auto discontinuities = system->discontinuitiesAtIC();
        if (discontinuities->size() == 0) break;
        if (std::find(discontinuities->begin(), discontinuities->end(), "REBOUND") != discontinuities->end())
        {
            preCollision();
            runCollisionDerivativeIC();
            runBasicCollision();
        }
    }
}

void SystemSolver::runPosIC()
{
    icTypeSolver = PosICNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runVelIC()
{
    icTypeSolver = VelICSolver::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runAccIC()
{
    icTypeSolver = AccICNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

bool SystemSolver::needToRedoPosIC()
{
    auto allRedunCons = allRedundantConstraints();
    auto newSet = std::make_shared<std::set<std::string>>();
    for (auto& con : *allRedunCons) {
        auto aaa = std::static_pointer_cast<RedundantConstraint>(con);
        auto& bbb = aaa->constraint->name;
        newSet->insert(bbb);
    }
    //std::transform(allRedunCons->begin(), allRedunCons->end(), newSet->begin(), [](auto con) {
    //    return std::static_pointer_cast<RedundantConstraint>(con)->constraint->name;
    //    });
    if (newSet->empty()) return false;
    auto itr = std::find_if(setsOfRedundantConstraints->begin(), setsOfRedundantConstraints->end(), [&](auto& set) {
        for (auto& name : *set) {
            if (newSet->find(name) == newSet->end()) return false;
        }
        return true;
        });
    if (itr != setsOfRedundantConstraints->end()) {
        //"Same set of redundant constraints found."
        setsOfRedundantConstraints->push_back(newSet);
        return false;
    }
    if (setsOfRedundantConstraints->size() >= 2) {
        auto it = std::find_if(setsOfRedundantConstraints->begin(), setsOfRedundantConstraints->end(), [&](auto set) {
            return set->size() == newSet->size();
            });
        if (it != setsOfRedundantConstraints->end()) {
            //"Equal number of redundant constraints found."
            setsOfRedundantConstraints->push_back(newSet);
            return false;
        }
    }
    setsOfRedundantConstraints->push_back(newSet);
    partsJointsMotionsLimitsDo([](auto item) { item->reactivateRedundantConstraints(); });
    return true;
}

void SystemSolver::preCollision()
{
}

void SystemSolver::runCollisionDerivativeIC()
{
}

void SystemSolver::runBasicCollision()
{
}

void SystemSolver::runBasicKinematic()
{
    if (tstart == tend) return;
    try {
        basicIntegrator = KineIntegrator::With();
        basicIntegrator->setSystem(this);
        basicIntegrator->run();
    }
    catch (const NotKinematicError& ex) {
        runQuasiKinematic();
    }
}

void SystemSolver::runPreDrag()
{
    initializeLocally();
    initializeGlobally();
    runPosIC();
}

void SystemSolver::runDragStep(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts)
{
    runPosICDrag(dragParts);
    runPosICDragLimit();
}

void SystemSolver::runQuasiKinematic()
{
    try {
        basicIntegrator = ICKineIntegrator::With();
        basicIntegrator->setSystem(this);
        basicIntegrator->run();
    }
    catch (DiscontinuityError ex) {
        discontinuityBlock();
    }
}

void SystemSolver::runBasicDynamic()
{
    try {
        basicIntegrator = DynIntegrator::With();
        basicIntegrator->setSystem(this);
        basicIntegrator->run();
    }
    catch (const DiscontinuityError& ex) {
        discontinuityBlock();
    }
}

void SystemSolver::runPosKine()
{
    icTypeSolver = PosKineNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runVelKine()
{
    icTypeSolver = VelKineSolver::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runAccKine()
{
    icTypeSolver = AccKineNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runPosICDrag(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts)
{
    auto newtonRaphson = PosICDragNewtonRaphson::With();
    newtonRaphson->setdragParts(dragParts);
    icTypeSolver = newtonRaphson;
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runPosICDragLimit()
{
    auto newtonRaphson = PosICDragLimitNewtonRaphson::With();
    icTypeSolver = newtonRaphson;
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runPosICKine()
{
    icTypeSolver = PosICKineNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runVelICKine()
{
    icTypeSolver = VelICKineSolver::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::runAccICKine()
{
    icTypeSolver = AccICKineNewtonRaphson::With();
    icTypeSolver->setSystem(this);
    icTypeSolver->run();
}

void SystemSolver::partsJointsMotionsLimitsDo(const std::function<void(std::shared_ptr<Item>)>& f)
{
    system->partsJointsMotionsLimitsDo(f);
}

void SystemSolver::logString(const std::string& str)
{
    system->logString(str);
}

std::shared_ptr<std::vector<std::shared_ptr<Part>>> SystemSolver::parts()
{
    return system->parts;
}

std::shared_ptr<std::vector<std::shared_ptr<LimitIJ>>> SystemSolver::limits()
{
    return system->limits;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> SystemSolver::essentialConstraints()
{
    return system->essentialConstraints();
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> SystemSolver::displacementConstraints()
{
    return system->displacementConstraints();
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> SystemSolver::perpendicularConstraints()
{
    return system->perpendicularConstraints();
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> SystemSolver::allRedundantConstraints()
{
    return system->allRedundantConstraints();
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> SystemSolver::allConstraints()
{
    return system->allConstraints();
}

void SystemSolver::postNewtonRaphson()
{
    throw SimulationStoppingError("To be implemented.");
}

void SystemSolver::partsJointsMotionsLimitsForcesTorquesDo(const std::function<void(std::shared_ptr<Item>)>& f)
{
    system->partsJointsMotionsLimitsForcesTorquesDo(f);
}

void SystemSolver::discontinuityBlock()
{
    throw SimulationStoppingError("To be implemented.");
}

double SystemSolver::startTime()
{
    return tstart;
}

double SystemSolver::outputStepSize()
{
    return hout;
}

double SystemSolver::maxStepSize()
{
    return hmax;
}

double SystemSolver::minStepSize()
{
    return hmin;
}

double SystemSolver::firstOutputTime()
{
    return toutFirst;
}

double SystemSolver::endTime()
{
    return tend;
}

void SystemSolver::settime(double tnew)
{
    system->mbdTimeValue(tnew);
}

void SystemSolver::errorTol(double tol)
{
    errorTolPosKine = tol;
    errorTolAccKine = tol;
    corAbsTol = tol;
    corRelTol = tol;
    intAbsTol = tol;
    intRelTol = tol;
}

double SystemSolver::integrationRelativeTolerance()
{
    if (intRelTol == 0.0) {
        return 1.0e-6;
    }
    else {
        return intRelTol;
    }
}

double SystemSolver::integrationAbsoluteTolerance()
{
    if (intAbsTol == 0.0) {
        return 1.0e-6;
    }
    else {
        return intAbsTol;
    }
}

double SystemSolver::correctorRelativeTolerance()
{
    if (corRelTol == 0.0) {
        return 1.0e-6;
    }
    else {
        return corRelTol;
    }
}

double SystemSolver::correctorAbsoluteTolerance()
{
    if (corAbsTol == 0.0) {
        return 1.0e-6;
    }
    else {
        return corAbsTol;
    }
}

void SystemSolver::tstartPastsAddFirst(double tstartPast)
{
    tstartPasts->insert(tstartPasts->begin(), tstartPast);
}

void SystemSolver::output()
{
    system->outputFor(DYNAMIC);
}

void SystemSolver::time(double t)
{
    system->mbdTimeValue(t);
}

bool SystemSolver::limitsSatisfied()
{
    return     system->limitsSatisfied();
}

void SystemSolver::deactivateLimits()
{
    system->deactivateLimits();
}

void System::deactivateLimits()
{
    std::for_each(limits->cbegin(), limits->cend(), [](auto& limit) { limit->deactivate(); });
}

void SystemSolver::useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
    system->useKineTrialStepStats(stats);
}

void SystemSolver::useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
    system->useDynTrialStepStats(stats);
}

void SystemSolver::useDAEStepStats(std::shared_ptr<SolverStatistics> stats)
{
    throw SimulationStoppingError("To be implemented.");
}
