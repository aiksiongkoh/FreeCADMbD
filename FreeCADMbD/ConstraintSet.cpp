/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>
#include <memory>
#include <typeinfo>

#include "ConstraintSet.h"
#include "Constraint.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "RedundantConstraint.h"
#include "MarkerFrame.h"
#include "ForceTorqueData.h"
#include "System.h"

using namespace MbD;

void ConstraintSet::constraintsDo(const std::function <void(std::shared_ptr<Constraint>)>& f) const
{
    std::for_each(constraints->begin(), constraints->end(), f);
}

void ConstraintSet::initialize()
{
    constraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
}

void ConstraintSet::initializeGlobally()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->initializeGlobally(); });
}

void ConstraintSet::initializeLocally()
{
    auto frmIqc = std::dynamic_pointer_cast<EndFrameqc>(eFrmI);
    if (frmIqc) {
        if (frmIqc->endFrameqct) {
            eFrmI = frmIqc->endFrameqct;
        }
    }
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->initializeLocally(); });
}

void ConstraintSet::addConstraint(std::shared_ptr<Constraint> con)
{
    con->owner = this;
    constraints->push_back(con);
}
void ConstraintSet::postInput()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postInput(); });
}

void ConstraintSet::prePosIC()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->prePosIC(); });
}

void ConstraintSet::prePosKine()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->prePosKine(); });
}

void ConstraintSet::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillEssenConstraints(con, essenConstraints); });
}

void ConstraintSet::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillDispConstraints(con, dispConstraints); });
}

void ConstraintSet::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPerpenConstraints(con, perpenConstraints); });
}

void ConstraintSet::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillConstraints(con, allConstraints); });
}

void ConstraintSet::fillqsulam(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillqsulam(col); });
}

void ConstraintSet::fillqsudot(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillqsudot(col); });
}

void ConstraintSet::fillqsudotWeights(DiagMatDsptr)
{
}

void ConstraintSet::useEquationNumbers()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->useEquationNumbers(); });
}

std::string ConstraintSet::constraintSpecs()
{
    std::stringstream ss;
    constraintsDo([&](std::shared_ptr<Constraint> con) {
        ss << con->constraintSpec() << std::endl;
        });
    return ss.str();
}

void ConstraintSet::setqsulam(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsulam(col); });
}

void ConstraintSet::setqsudotlam(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsudotlam(col); });
}

void ConstraintSet::postPosICIteration()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postPosICIteration(); });
}

void ConstraintSet::fillPosICError(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosICError(col); });
}

void ConstraintSet::fillPosICJacob(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosICJacob(mat); });
}

void ConstraintSet::postPosIC()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postPosIC(); });
}

void ConstraintSet::preDyn()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preDyn(); });
}

void ConstraintSet::fillPosKineError(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosKineError(col); });
}

void ConstraintSet::fillPosKineJacob(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillPosKineJacob(mat); });
}

void ConstraintSet::fillqsuddotlam(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillqsuddotlam(col); });
}

void ConstraintSet::preVelIC()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preVelIC(); });
}

void ConstraintSet::fillVelICError(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillVelICError(col); });
}

void ConstraintSet::fillVelICJacob(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillVelICJacob(mat); });
}

void ConstraintSet::preAccIC()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preAccIC(); });
}

void ConstraintSet::fillAccICIterError(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillAccICIterError(col); });
}

void ConstraintSet::fillAccICIterJacob(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillAccICIterJacob(mat); });
}

void ConstraintSet::setqsuddotlam(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsuddotlam(col); });
}

void ConstraintSet::postDynStep()
{
    constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postDynStep(); });
}

void ConstraintSet::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    eFrmI = frmi;
    eFrmJ = frmj;
}

FColDsptr ConstraintSet::aFIeJtIe() const
{
    //"aFIeJtIe is joint force on end frame Ie expresses in Ie components."
    auto frmIqc = std::dynamic_pointer_cast<EndFrameqc>(eFrmI);
    return frmIqc->aAeO()->timesFullColumn(aFIeJtO());
}

FColDsptr ConstraintSet::aFIeJtO() const
{
    //"aFIeJtO is joint force on end frame Ie expresses in O components."
    auto aFIeJtO = std::make_shared <FullColumn<double>>(3);
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointForceI(aFIeJtO); });
    return aFIeJtO;
}

void ConstraintSet::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillRedundantConstraints(con, redunConstraints); });
}

void ConstraintSet::fillpqsumu(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpqsumu(col); });
}

void ConstraintSet::fillpqsumudot(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpqsumudot(col); });
}

void ConstraintSet::setpqsumu(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumu(col); });
}

void ConstraintSet::setpqsumudot(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumudot(col); });
}

void ConstraintSet::postDynPredictor()
{
    constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynPredictor(); });
}

void ConstraintSet::fillDynError(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillDynError(col); });
}

void ConstraintSet::fillpFpy(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpFpy(mat); });
}

void ConstraintSet::fillpFpydot(SpMatDsptr mat)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpFpydot(mat); });
}

void ConstraintSet::postDynCorrectorIteration()
{
    constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynCorrectorIteration(); });
}

void ConstraintSet::postDynOutput()
{
    constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynOutput(); });
}

void ConstraintSet::preDynOutput()
{
    constraintsDo([](std::shared_ptr<Constraint> con) { con->preDynOutput(); });
}

void ConstraintSet::setpqsumuddot(FColDsptr col)
{
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumuddot(col); });
}

void ConstraintSet::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
    for (size_t i = 0; i < constraints->size(); i++)
    {
        auto& constraint = constraints->at(i);
        if (std::find(redundantEqnNos->begin(), redundantEqnNos->end(), constraint->iG) != redundantEqnNos->end()) {
            auto redunCon = RedundantConstraint::With();
            redunCon->constraint = constraint;
            constraints->at(i) = redunCon;
        }
    }
}

void ConstraintSet::reactivateRedundantConstraints()
{
    for (size_t i = 0; i < constraints->size(); i++)
    {
        auto& con = constraints->at(i);
        if (con->isRedundant()) {
            constraints->at(i) = std::static_pointer_cast<RedundantConstraint>(con)->constraint;
        }
    }
}

void ConstraintSet::constraintsReport()
{
    auto redunCons = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
    constraintsDo([&](std::shared_ptr<Constraint> con) {
        if (con->isRedundant()) {
            redunCons->push_back(con);
        }
        });
    if (redunCons->size() > 0) {
        std::string str = "MbD: " + classname() + std::string(" ") + name + " has the following constraint(s) removed: ";
        logString(str);
        std::for_each(redunCons->begin(), redunCons->end(), [&](auto& con) {
            str = "MbD: " + std::string("    ") + con->classname();
            logString(str);
            });
    }
}

std::shared_ptr<StateData> ConstraintSet::stateData()
{
    //"
    //MbD returns aFIeO and aTIeO.
    //GEO needs aFImO and aTImO.
    //For Motion rImIeO is not zero and is changing.
    //aFImO : = aFIeO.
    //aTImO : = aTIeO + (rImIeO cross : aFIeO).
    //"

    auto answer = std::make_shared<ForceTorqueData>();
    auto aFIeO = aFX();
    auto aTIeO = aTX();
    auto rImIeO = eFrmI->rmeO();
    answer->aFIO = aFIeO;
    answer->aTIO = aTIeO->plusFullColumn(rImIeO->cross(aFIeO));
    return answer;
}

FColDsptr ConstraintSet::aFX() const
{
    return jointForceI();
}

FColDsptr ConstraintSet::aTIeJtIe() const
{
    //"aTIeJtIe is torque on part containing end frame Ie expressed in Ie components."
    return eFrmI->aAeO()->timesFullColumn(aTIeJtO());
}

FColDsptr ConstraintSet::aTIeJtO() const
{
    //"aTIeJtO is torque on part containing end frame Ie expressed in O components."
    auto aTIeJtO = std::make_shared <FullColumn<double>>(3);
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointTorqueI(aTIeJtO); });
    return aTIeJtO;
}

FColDsptr ConstraintSet::jointForceI() const
{
    //"jointForceI is force on MbD marker I."
    auto jointForce = std::make_shared <FullColumn<double>>(3);
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointForceI(jointForce); });
    return jointForce;
}

FColDsptr ConstraintSet::aTX() const
{
    return jointTorqueI();
}

FColDsptr ConstraintSet::jointTorqueI() const
{
    //"jointTorqueI is torque on MbD marker I."
    auto jointTorque = std::make_shared <FullColumn<double>>(3);
    constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointTorqueI(jointTorque); });
    return jointTorque;
}
