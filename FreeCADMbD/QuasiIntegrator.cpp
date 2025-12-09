/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "QuasiIntegrator.h"
#include "Item.h"
#include "SystemSolver.h"
#include "BasicQuasiIntegrator.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"
#include "TooSmallStepSizeError.h"
#include "TooManyTriesError.h"
#include "SingularMatrixError.h"
#include "DiscontinuityError.h"

using namespace MbD;

std::shared_ptr<QuasiIntegrator> QuasiIntegrator::With()
{
    auto inst = std::make_shared<QuasiIntegrator>();
    inst->initialize();
    return inst;
}

void QuasiIntegrator::initialize()
{
    Solver::initialize();
    integrator = BasicQuasiIntegrator::With();
    integrator->setSystem(this);
}

void QuasiIntegrator::preRun()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDyn(); });
}

void QuasiIntegrator::run()
{
    try {
        try {
            try {
                preRun();
                initializeLocally();
                initializeGlobally();
                if (hout > (4 * std::numeric_limits<double>::epsilon()) && (direction * tout < (direction * (tend + (0.1 * direction * hout))))) {
                    integrator->run();
                }
                finalize();
                reportStats();
                postRun();
            }
            catch (SingularMatrixError ex) {
                std::stringstream ss;
                ss << "MbD: Solver has encountered a singular matrix." << std::endl;
                ss << "MbD: Check to see if a massless or a very low mass part is under constrained." << std::endl;
                ss << "MbD: Check to see if the system is in a locked position." << std::endl;
                ss << "MbD: Check to see if the error tolerance is too demanding." << std::endl;
                ss << "MbD: Check to see if a curve-curve is about to have multiple contact points." << std::endl;
                auto str = ss.str();
                logString(str);
                throw SimulationStoppingError("");
            }
        }
        catch (TooSmallStepSizeError ex) {
            std::stringstream ss;
            ss << "MbD: Step size is prevented from going below the user specified minimum." << std::endl;
            ss << "MbD: Check to see if the system is in a locked position." << std::endl;
            ss << "MbD: Check to see if a curve-curve is about to have multiple contact points." << std::endl;
            ss << "MbD: If they are not, lower the permitted minimum step size." << std::endl;
            auto str = ss.str();
            logString(str);
            throw SimulationStoppingError("");
        }
    }
    catch (TooManyTriesError ex) {
        std::stringstream ss;
        ss << "MbD: Check to see if the error tolerance is too demanding." << std::endl;
        auto str = ss.str();
        logString(str);
        throw SimulationStoppingError("");
    }

}

void QuasiIntegrator::reportStats()
{
    //Do nothing
}

void QuasiIntegrator::preFirstStep()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynFirstStep(); });
}

void QuasiIntegrator::postFirstStep()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynFirstStep(); });
    if (integrator->istep > 0) {
        //"Noise make checking at the start unreliable."
        checkForDiscontinuity();
    }
    checkForOutputThrough(integrator->t);
}

void QuasiIntegrator::preStep()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynStep(); });
}

void QuasiIntegrator::checkForDiscontinuity()
{
    //"Check for discontinuity in (tpast,t] or [t,tpast) if integrating 
    //backward."

    auto t = integrator->t;
    auto tprevious = integrator->tprevious();
    auto epsilon = std::numeric_limits<double>::epsilon();
    double tstartNew;
    if (direction == 0) {
        tstartNew = epsilon;
    }
    else {
        epsilon = std::abs(t) * epsilon;
        tstartNew = ((direction * t) + epsilon) / direction;
    }
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { tstartNew = item->checkForDynDiscontinuityBetweenand(tprevious, tstartNew); });
    if ((direction * tstartNew) > (direction * t)) {
        //"No discontinuity in step"
        return;
    }
    else {
        checkForOutputThrough(tstartNew);
        interpolateAt(tstartNew);
        system->tstartPastsAddFirst(tstart);
        system->tstart = tstartNew;
        system->toutFirst = tout;
        auto discontinuityTypes = std::make_shared<std::vector<DiscontinuityType>>();
        system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->discontinuityAtaddTypeTo(tstartNew, discontinuityTypes); });
        throwDiscontinuityError("", discontinuityTypes);
    }
}

double QuasiIntegrator::suggestSmallerOrAcceptFirstStepSize(double hnew)
{
    auto hnew2 = hnew;
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { hnew2 = item->suggestSmallerOrAcceptDynFirstStepSize(hnew2); });
    if (hnew2 > hmax) {
        hnew2 = hmax;
        std::string str = "StM: Step size is at user specified maximum.";
        logString(str);
    }
    if (hnew2 < hmin) {
        std::stringstream ss;
        ss << "StM: Step size " << hnew2 << " < " << hmin << " user specified minimum.";
        auto str = ss.str();
        logString(str);
        throw TooSmallStepSizeError("");
    }
    return hnew2;
}

double QuasiIntegrator::suggestSmallerOrAcceptStepSize(double hnew)
{
    auto hnew2 = hnew;
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { hnew2 = item->suggestSmallerOrAcceptDynStepSize(hnew2); });
    if (hnew2 > hmax) {
        hnew2 = hmax;
        system->logString("StM: Step size is at user specified maximum.");
    }
    if (hnew2 < hmin) {
        std::stringstream ss;
        ss << "StM: Step size " << hnew2 << " < " << hmin << " user specified minimum.";
        auto str = ss.str();
        system->logString(str);
        throw TooSmallStepSizeError("");
    }
    return hnew2;
}

void QuasiIntegrator::incrementTime(double tnew)
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->storeDynState(); });
    IntegratorInterface::incrementTime(tnew);
}

void QuasiIntegrator::throwDiscontinuityError(const std::string& str, std::shared_ptr<std::vector<DiscontinuityType>> discontinuityTypes)
{
    throw DiscontinuityError(str, discontinuityTypes);
}

void QuasiIntegrator::checkForOutputThrough(double t)
{
    //"Kinematic analysis is done at every tout."
    if (direction * t <= (direction * (tend + (0.1 * direction * hout)))) {
        if (std::abs(tout - t) < 1.0e-12) {
            system->output();
            tout += direction * hout;
        }
    }
    else {
        integrator->_continue = false;
    }
}

void QuasiIntegrator::interpolateAt(double tArg)
{
    //"Interpolate for system state at tArg and leave system in that state."
    system->time(tArg);
    runInitialConditionTypeSolution();
}

void QuasiIntegrator::postStep()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynStep(); });

    if (integrator->istep > 0) {
        //"Noise make checking at the start unreliable."
        checkForDiscontinuity();
    }
    checkForOutputThrough(integrator->t);
}

void QuasiIntegrator::postRun()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDyn(); });
}

void QuasiIntegrator::useTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
    system->useDynTrialStepStats(stats);
}

void QuasiIntegrator::useQuasiStepStats(std::shared_ptr<SolverStatistics> stats)
{
    //Do Nothing
}
