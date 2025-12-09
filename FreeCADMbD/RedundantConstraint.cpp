/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RedundantConstraint.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<RedundantConstraint> RedundantConstraint::With()
{
    auto inst = std::make_shared<RedundantConstraint>();
    inst->initialize();
    return inst;
}

void RedundantConstraint::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>>)
{
    throw SimulationStoppingError("To be implemented.");
}

bool RedundantConstraint::isRedundant()
{
    return true;
}

std::string RedundantConstraint::classname()
{
    auto str = Item::classname() + "->" + constraint->classname();
    return str;
}

ConstraintType RedundantConstraint::type()
{
    return redundant;
}

void RedundantConstraint::fillqsuddotlam(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::fillqsulam(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::fillpqsumu(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::fillpqsumudot(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::postInput()
{
    //Do nothing.
}

void RedundantConstraint::prePosIC()
{
    //Do nothing.
}

void RedundantConstraint::fillEssenConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    //Do nothing.
}

void RedundantConstraint::fillDispConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    //Do nothing.
}

void RedundantConstraint::fillPerpenConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    //Do nothing.
}

void RedundantConstraint::fillConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
    //Do nothing.
}

void RedundantConstraint::fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    redunConstraints->push_back(sptr);
}

void RedundantConstraint::setqsulam(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::setqsudotlam(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::fillPosICError(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::fillPosKineError(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::fillPosKineJacob(SpMatDsptr)
{
    //Do nothing.
}

void RedundantConstraint::preVelIC()
{
    //Do nothing.
}

void RedundantConstraint::preAccIC()
{
    //Do nothing.
}

void RedundantConstraint::fillAccICIterError(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::setqsuddotlam(FColDsptr)
{
    //Do nothing.
}

void RedundantConstraint::discontinuityAtaddTypeTo(double, std::shared_ptr<std::vector<DiscontinuityType>>)
{
    //"Reactivate all constraints."
    throw SimulationStoppingError("To be implemented.");
    //| newSelf |
    //newSelf : = self constraint.
    //newSelf discontinuityAt : tstartNew addTypeTo : collection.
    //self become : newSelf
}

void RedundantConstraint::setpqsumu(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::setpqsumudot(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::setpqsumuddot(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::postDynPredictor()
{
    //Do nothing.
}

void RedundantConstraint::postPosICIteration()
{
    //Do nothing.
}

void RedundantConstraint::fillDynError(FColDsptr col)
{
    //Do nothing.
}

void RedundantConstraint::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void RedundantConstraint::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void RedundantConstraint::postDynCorrectorIteration()
{
    //Do nothing.
}

void RedundantConstraint::preDynOutput()
{
    //Do nothing.
}

void RedundantConstraint::postDynOutput()
{
    //Do nothing.
}

void RedundantConstraint::addToJointTorqueI(FColDsptr col)
{
    //Do nothing.
}

std::string RedundantConstraint::constraintSpec()
{
    return "RedundantConstraint" + constraint->constraintSpec();
}
