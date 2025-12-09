/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "System.h"
#include "Part.h"
#include "ConstraintSet.h"
#include "JointIJ.h"
#include "LimitIJ.h"
#include "ForceTorqueIJ.h"
#include "SystemSolver.h"
#include "SymTime.h"
#include "ExternalSystem.h"
#include "PrescribedMotion.h"
#include "SimulationStoppingError.h"

using namespace MbD;

System::System(const std::string& str) : Item(str) {
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<System> System::With()
{
    auto inst = std::make_shared<System>();
    inst->initialize();
    return inst;
}

std::shared_ptr<System> System::With(const std::string& str)
{
    auto inst = std::make_shared<System>(str);
    inst->initialize();
    return inst;
}

void System::initialize()
{
    externalSystem = std::make_shared<ExternalSystem>();
    time = std::make_shared<SymTime>();
    parts = std::make_shared<std::vector<std::shared_ptr<Part>>>();
    joints = std::make_shared<std::vector<std::shared_ptr<JointIJ>>>();
    motions = std::make_shared<std::vector<std::shared_ptr<PrescribedMotion>>>();
    limits = std::make_shared<std::vector<std::shared_ptr<LimitIJ>>>();
    forcesTorques = std::make_shared<std::vector<std::shared_ptr<ForceTorqueIJ>>>();
    fields = std::make_shared<std::vector<std::shared_ptr<ConstantGravity>>>();
    systemSolver = std::make_shared<SystemSolver>(this);
}

System* System::root()
{
    return this;
}

void System::addPart(std::shared_ptr<Part> part)
{
    part->setSystem(this);
    parts->push_back(part);
}

void System::addJoint(std::shared_ptr<JointIJ> joint)
{
    joint->owner = this;
    joints->push_back(joint);
}

void System::addMotion(std::shared_ptr<PrescribedMotion> motion)
{
    motion->owner = this;
    motions->push_back(motion);
}

void System::addLimit(std::shared_ptr<LimitIJ> limit)
{
    limit->owner = this;
    limits->push_back(limit);
}

void System::addForceTorque(std::shared_ptr<ForceTorqueIJ> forTor)
{
    forTor->owner = this;
    forcesTorques->push_back(forTor);
}

void System::addGravity(std::shared_ptr<ConstantGravity> grav)
{
    grav->owner = this;
    fields->push_back(grav);
}

void System::calcCharacteristicDimensions()
{
    //mbdUnits are in SI units at input.
    auto unitTime = calcCharacteristicTime();
    auto unitMass = calcCharacteristicMass();
    auto unitLength = calcCharacteristicLength();
    auto unitAngle = 1.0;
    mbdUnits = std::make_shared<Units>(unitTime, unitMass, unitLength, unitAngle);
    mbdUnits = std::make_shared<Units>(1.0, 1.0, 1.0, 1.0);    //for debug
}

double System::calcCharacteristicTime() const
{
    return std::abs(systemSolver->hout);
}

double System::calcCharacteristicMass() const
{
    auto n = parts->size();
    double sumOfSquares = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        auto mass = parts->at(i)->m;
        sumOfSquares += mass * mass;
    }
    auto rmsMass = std::sqrt(sumOfSquares / n);
    if (rmsMass <= 0) rmsMass = 1.0;
    return rmsMass;
}

double System::calcCharacteristicLength() const
{
    auto lengths = std::make_shared<std::vector<double>>();
    auto connectorList = this->connectorList();
    for (auto& connector : *connectorList) {
        auto eFrmI = connector->geteFrmI();
        lengths->push_back(eFrmI->rpmp()->length());
        auto eFrmJ = connector->geteFrmJ();
        lengths->push_back(eFrmJ->rpmp()->length());
    }
    auto n = lengths->size();
    double sumOfSquares = std::accumulate(lengths->begin(), lengths->end(), 0.0, [](double sum, double l) { return sum + l * l; });
    auto rmsLength = std::sqrt(sumOfSquares / std::max(n, size_t(1)));
    if (rmsLength <= 0) rmsLength = 1.0;
    return rmsLength;
}

void System::runKINEMATIC(std::shared_ptr<System> self)
{
    externalSystem->preMbDrun(self);
    while (true)
    {
        initializeLocally();
        initializeGlobally();
        if (!hasChanged) break;
    }
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
    externalSystem->outputFor(INPUT);
    systemSolver->runAllIC();
    externalSystem->outputFor(INITIALCONDITION);
    systemSolver->runBasicKinematic();
    externalSystem->postMbDrun();
}

void System::runDYNAMIC(std::shared_ptr<System> self)
{
    externalSystem->preMbDrun(self);
    calcCharacteristicDimensions();
    while (true)
    {
        initializeLocally();
        initializeGlobally();
        if (!hasChanged) break;
    }
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
    externalSystem->outputFor(INPUT);
    systemSolver->runAllIC();
    externalSystem->outputFor(INITIALCONDITION);
    systemSolver->runBasicDynamic();
    externalSystem->postMbDrun();
}

void System::initializeLocally()
{
    hasChanged = false;
    time->value = systemSolver->tstart;
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->initializeLocally(); });
    systemSolver->initializeLocally();
}

void System::initializeGlobally()
{
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->initializeGlobally(); });
    systemSolver->initializeGlobally();
}

void System::clear()
{
    name = std::string();
    parts->clear();
    joints->clear();
    motions->clear();
    forcesTorques->clear();
    fields->clear();
}

void System::runPreDrag(std::shared_ptr<System> self)
{
    externalSystem->preMbDrun(self);
    while (true)
    {
        initializeLocally();
        initializeGlobally();
        if (!hasChanged) break;
    }
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
    systemSolver->runPreDrag();
    externalSystem->updateFromMbD();
}

void System::runDragStep(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts) const
{
    partsJointsMotionsLimitsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
    systemSolver->runDragStep(dragParts);
    externalSystem->updateFromMbD();
}

std::shared_ptr<std::vector<std::string>> System::discontinuitiesAtIC()
{
    return std::make_shared<std::vector<std::string>>();
}

void System::jointsMotionsLimitsDo(const std::function<void(std::shared_ptr<ConstraintSet>)>& f) const
{
    std::for_each(joints->begin(), joints->end(), f);
    std::for_each(motions->begin(), motions->end(), f);
    std::for_each(limits->begin(), limits->end(), f);
}

void System::partsJointsMotionsLimitsForcesTorquesDo(const std::function<void(std::shared_ptr<Item>)>& f) const
{
    std::for_each(parts->begin(), parts->end(), f);
    std::for_each(joints->begin(), joints->end(), f);
    std::for_each(motions->begin(), motions->end(), f);
    std::for_each(limits->begin(), limits->end(), f);
    std::for_each(forcesTorques->begin(), forcesTorques->end(), f);
    std::for_each(fields->begin(), fields->end(), f);
}

void System::partsJointsMotionsLimitsDo(const std::function<void(std::shared_ptr<Item>)>& f) const
{
    std::for_each(parts->begin(), parts->end(), f);
    std::for_each(joints->begin(), joints->end(), f);
    std::for_each(motions->begin(), motions->end(), f);
    std::for_each(limits->begin(), limits->end(), f);
}

void System::logString(const std::string& str)
{
    externalSystem->logString(str);
}

double System::mbdTimeValue() const
{
    return time->getValue();
}

void System::mbdTimeValue(double t) const
{
    time->setValue(t);
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::essentialConstraints() const
{
    auto essenConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->fillEssenConstraints(essenConstraints); });
    return essenConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::displacementConstraints() const
{
    auto dispConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    jointsMotionsLimitsDo([&](std::shared_ptr<ConstraintSet> joint) { joint->fillDispConstraints(dispConstraints); });
    return dispConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::perpendicularConstraints() const
{
    auto perpenConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    jointsMotionsLimitsDo([&](std::shared_ptr<ConstraintSet> joint) { joint->fillPerpenConstraints(perpenConstraints); });
    return perpenConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::allRedundantConstraints() const
{
    auto redunConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->fillRedundantConstraints(redunConstraints); });
    return redunConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::allConstraints() const
{
    auto constraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->fillConstraints(constraints); });
    return constraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Item>>> System::connectorList() const
{
    auto list = std::make_shared<std::vector<std::shared_ptr<Item>>>();
    list->insert(list->end(), joints->begin(), joints->end());
    list->insert(list->end(), motions->begin(), motions->end());
    list->insert(list->end(), limits->begin(), limits->end());
    list->insert(list->end(), forcesTorques->begin(), forcesTorques->end());
    return list;
}

double System::maximumMass() const
{
    auto maxPart = std::max_element(parts->begin(), parts->end(), [](auto& a, auto& b) { return a->m < b->m; });
    return maxPart->get()->m;
}

double System::maximumMomentOfInertia() const
{
    double max = 0.0;
    for (size_t i = 0; i < parts->size(); i++)
    {
        auto& part = parts->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto& aJ = part->aJ;
            auto aJi = aJ->at(j);
            if (max < aJi) max = aJi;
        }
    }
    return max;
}

double System::translationLimit() const
{
    return systemSolver->translationLimit;
}

double System::rotationLimit() const
{
    return systemSolver->rotationLimit;
}

void System::outputFor(AnalysisType type) const
{
    externalSystem->outputFor(type);
}

bool System::limitsSatisfied() const
{
    return  std::all_of(limits->cbegin(), limits->cend(), [](auto& limit) { return limit->satisfied(); });
}

void System::useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats) const
{
    externalSystem->useKineTrialStepStats(stats);
}

void System::useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats) const
{
    externalSystem->useDynTrialStepStats(stats);
}
