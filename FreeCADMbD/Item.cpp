/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include <windows.h>
#include <assert.h>
//#include <debugapi.h>
#include <sstream> 
#include <chrono>

#include "Item.h"
#include "System.h"
#include "Symbolic.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Item::Item() {
}

std::shared_ptr<Item> Item::With(const std::string& str)
{
    auto inst = std::make_shared<Item>(str);
    inst->initialize();
    return inst;
}

void Item::initialize()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto nanoseconds = now.time_since_epoch().count();
    name = std::to_string(nanoseconds);
}

System* Item::root()
{
    return owner->root();
}

void Item::noop()
{
    //No Operations
}

std::ostream& Item::printOn(std::ostream& s) const
{
    const std::string& str = typeid(*this).name();
    auto classname = str.substr(11, str.size() - 11);
    s << classname << std::endl;
    return s;
}

bool Item::isJointForce()
{
    return false;
}

bool Item::isJointTorque()
{
    return false;
}

bool Item::isKinedotIJ()
{
    return false;
}

bool Item::isKineIJ()
{
    return false;
}

void Item::initializeGlobally()
{
    //"Called once only."
    //"Initialize all constant dependent instance variables using local and global objects."
    //"Default is do nothing."
}

void Item::initializeLocally()
{
    //"Called once only."
    //"Assume that the independent instance variables are already set."
    //"Initialize all constant dependent instance variables using local objects only."
    //"Default is do nothing."
}

void MbD::Item::useUniqueDispIeJeO()
{
}

void MbD::Item::useUniqueDispIeJeKe()
{
}

void Item::postInput()
{
    //Called once after input
    simUpdateAll();
}

void Item::simUpdateAll()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::checkForCollisionDiscontinuityBetweenand(double, double)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::setpqsumu(FColDsptr col)
{
    (void)col;
}

void Item::setpqsumuddot(FColDsptr col)
{
    (void)col;
}

void Item::setpqsumudot(FColDsptr col)
{
    (void)col;
}

void Item::reactivateRedundantConstraints()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::registerName()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillPosKineError(FColDsptr col)
{
    (void)col;
}

void Item::fillPosKineJacob(SpMatDsptr mat)
{
    (void)mat;
}

void Item::fillpqsumu(FColDsptr col)
{
    (void)col;
}

void Item::fillpqsumudot(FColDsptr col)
{
    (void)col;
}

void Item::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillpFpy(SpMatDsptr mat)
{
    (void)mat;
}

void Item::fillpFpydot(SpMatDsptr mat)
{
    (void)mat;
}

void Item::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillStaticError(FColDsptr col)
{
    // Do nothing.
}

void Item::fillStaticJacob(SpMatDsptr mat)
{
    // Do nothing.
}

void Item::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillDynError(FColDsptr col)
{
    (void)col;
}

void Item::fillqsu(FColDsptr col)
{
    (void)col;
}

void Item::fillqsuWeights(DiagMatDsptr mat)
{
    (void)mat;
}

void Item::fillqsuWeightsSmall(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillqsulam(FColDsptr col)
{
    (void)col;
}

void Item::setqsulam(FColDsptr col)
{
    (void)col;
}

void Item::preDyn()
{
    //"Assume positions, velocities and accelerations are valid."
    //"Called once before solving for dynamic solution."
    //"Update all variable dependent instance variables needed for runDYNAMICS even if they 
    //have been calculated in postPosIC, postVelIC and postAccIC."
    //"Calculate p, pdot."
    //"Default is do nothing."
}

void Item::preDynCorrector()
{
    //Do nothing
}

void Item::preDynCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postDyn()
{
    //"Assume runDYNAMICS ended successfully."
    //"Called once at the end of runDYNAMICS."
    //"Update all instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) 
    //regardless of whether they are needed."
    //"This is a subset of update."
    //"Default is do nothing."
}

void Item::postDynCorrector()
{
    //Do nothing.
}

void Item::postDynCorrectorIteration()
{
    //"Called after the predictor stage in the dynamic solution."
    //"Update only instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) that are needed for the corrector stage."

    simUpdateAll();
}

std::string Item::classname()
{
    const std::string& str = typeid(*this).name();
    auto answer = str.substr(11, str.size() - 11);
    return answer;
}

void Item::preDynFirstStep()
{
    //"Called before the start of the first step in the dynamic solution."
    preDynStep();
}

void Item::preDynOutput()
{
    //"Calculate all instance variables just before output."
    simUpdateAll();
}

void Item::preDynPredictor()
{
    //"Do nothing"
}

void Item::postDynFirstStep()
{
    postDynStep();
}

void Item::postDynOutput()
{
    //"Do nothing"
}

void Item::postDynPredictor()
{
    //"Called after the predictor stage in the dynamic solution."
    //"Update only instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) 
    //that are needed for the corrector stage."
    //"Needless updating can be expensive here."
    //"This is a subset of update."
    //"Default is do nothing."
    //"updateInSimulation is the interface to the old system."

    simUpdateAll();
}

void Item::preDynStep()
{
    //Do nothing.
}

void Item::preICRestart()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postDynStep()
{
    //"Called after the end of a complete step in the dynamic solution."
    //"Update info before checking for discontinuities."
    //"Default is do nothing."
}

void Item::storeDynState()
{
    //Do nothing.
}

double Item::suggestSmallerOrAcceptCollisionFirstStepSize(double)
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

double Item::suggestSmallerOrAcceptCollisionStepSize(double)
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

double Item::suggestSmallerOrAcceptDynFirstStepSize(double hnew)
{
    //"Default is return hnew."
    //"Best to do nothing so as not to disrupt the starting algorithm."
    return hnew;
}

double Item::suggestSmallerOrAcceptDynStepSize(double hnew)
{
    //"Default is return hnew."
    return hnew;
}

void Item::preVelIC()
{
    //"Assume positions are valid."
    //"Called once before solving for velocity initial conditions."
    //"Update all variable dependent instance variables needed for velIC even if they have 
    //been calculated in postPosIC."
    //"Variables dependent on t are updated."

    simUpdateAll();
}

void Item::postVelIC()
{
    //Do nothing.
}

void Item::fillqsudot(FColDsptr col)
{
    (void)col;
}

void Item::fillqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillqsudotWeights(DiagMatDsptr mat)
{
    (void)mat;
}

void Item::fillVelICError(FColDsptr col)
{
    (void)col;
}

void Item::fillVelICJacob(SpMatDsptr mat)
{
    (void)mat;   // suppress unused parameter warning
}

void Item::getString(const std::string& str)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::setqsudotlam(FColDsptr col)
{
    (void)col;
}

void Item::setqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::setqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::preAccIC()
{
    simUpdateAll();
}

void Item::preCollision()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::preCollisionCorrector()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::preCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::preCollisionDerivativeIC()
{
    //Solve for collision derivative initial conditions.
    throw SimulationStoppingError("To be implemented.");
}

void Item::preCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::preCollisionStep()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postAccIC()
{
    //Do nothing.
}

void Item::postAccICIteration()
{
    //Do nothing.
}

void Item::postCollisionCorrector()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postCollisionDerivativeIC()
{
    //Solve for collision derivative initial conditions.
    throw SimulationStoppingError("To be implemented.");
}

void Item::postCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::postCollisionStep()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillqsuddotlam(FColDsptr col)
{
    (void)col;
}

void Item::fillAccICIterError(FColDsptr col)
{
    (void)col;
}

void Item::fillAccICIterJacob(SpMatDsptr mat)
{
    (void)mat;
}

void Item::fillCollisionDerivativeICError(FColDsptr col)
{
    //Solve for collision derivative initial conditions.
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillCollisionDerivativeICJacob(SpMatDsptr mat)
{
    //Solve for collision derivative initial conditions.
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillCollisionError(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillCollisionpFpy(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::fillCollisionpFpydot(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::setqsudot(FColDsptr col)
{
    (void)col;
}

void Item::setqsuddotlam(FColDsptr col)
{
    (void)col;
}

std::shared_ptr<StateData> Item::stateData()
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<StateData>();
}

void Item::storeCollisionState()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::discontinuityAtaddTypeTo(double, std::shared_ptr<std::vector<DiscontinuityType>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::discontinuityAtICAddTo(std::shared_ptr<std::vector<DiscontinuityType>>)
{
    //Used by CurveCurveContactJoint
    throw SimulationStoppingError("To be implemented.");
}

double Item::checkForDynDiscontinuityBetweenand(double, double t)
{
    //"Check for discontinuity in the last step defined by the interval (tprevious,t]."
    //"Default is assume no discontinuity and return t."
    return t;
}

void Item::constraintsReport()
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::setqsu(FColDsptr col)
{
    (void)col;
}

void Item::useEquationNumbers()
{
    //Do nothing.
}

double Item::value()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

void Item::logString(const std::string& str)
{
    root()->logString(str);
}

void Item::logStringwithArgument(const std::string&, const std::string&)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::logStringwithArguments(const std::string&, std::shared_ptr<std::vector<std::string&>>)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::normalImpulse(double)
{
    throw SimulationStoppingError("To be implemented.");
}

void Item::prePosIC()
{
    //"Called once before solving for position initial conditions."
    //"Update all variable dependent instance variables needed for posIC."
    //"This is a subset of update."

    simUpdateAll();
}

void Item::prePosKine()
{
    prePosIC();
}

void Item::preStatic()
{
    simUpdateAll();
}

void Item::postPosIC()
{
    //Do nothing.
}

void Item::postPosICIteration()
{
    simUpdateAll();
}

void Item::postStatic()
{
	// Assume runSTATICS ended successfully.
	// Called once at the end of runSTATICS.
	// Update all instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) 
	// regardless of whether they are needed.
	// Default is do nothing.
}

void Item::postStaticIteration()
{
    simUpdateAll();
}

void Item::fillPosICError(FColDsptr col)
{
    (void)col;
}

void Item::fillPosICJacob(SpMatDsptr mat)
{
    (void)mat;
}

std::ostream& MbD::operator<<(std::ostream& s, const Item& item)
{
    if (&item) {
        return item.printOn(s);
    }
    else {
        s << "NULL";
    }
    return s;
}

