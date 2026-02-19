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

void MbD::RedundantConstraint::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    //Do nothing.
}

void MbD::RedundantConstraint::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
    //Do nothing.
}

void MbD::RedundantConstraint::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    //Do nothing.
}

void MbD::RedundantConstraint::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
    //Do nothing.
}

void MbD::RedundantConstraint::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    //Do nothing.
}

void RedundantConstraint::fillqsuddotlam(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillqsulam(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillpqsumu(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillpqsumudot(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::postInput()
{
    //Do nothing.
}

void RedundantConstraint::prePosIC()
{
    //Do nothing.
}

void RedundantConstraint::setqsulam(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::setqsudotlam(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillPosICError(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillPosKineError(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::fillPosKineJacob(SpMatDsptr mat)
{
    (void)mat;
}

void RedundantConstraint::preVelIC()
{
    //Do nothing.
}

void RedundantConstraint::preAccIC()
{
    //Do nothing.
}

void RedundantConstraint::fillAccICIterError(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::setqsuddotlam(FColDsptr col)
{
    (void)col;
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
    (void)col;
}

void RedundantConstraint::setpqsumudot(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::setpqsumuddot(FColDsptr col)
{
    (void)col;
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
    (void)col;
}

void RedundantConstraint::fillpFpy(SpMatDsptr mat)
{
    (void)mat;
}

void RedundantConstraint::fillpFpydot(SpMatDsptr mat)
{
    (void)mat;
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

void MbD::RedundantConstraint::addToJointForceI(FColDsptr col)
{
    (void)col;
}

void RedundantConstraint::addToJointTorqueI(FColDsptr col)
{
    (void)col;
}

void MbD::RedundantConstraint::addToJointForceJ(FColDsptr col)
{
    (void)col;
}

void MbD::RedundantConstraint::addToJointTorqueJ(FColDsptr col)
{
    (void)col;
}

std::string RedundantConstraint::constraintSpec()
{
    return "RedundantConstraint" + constraint->constraintSpec();
}
