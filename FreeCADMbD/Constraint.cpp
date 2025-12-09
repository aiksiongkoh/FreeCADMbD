/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <functional>
#include <chrono>
#include <cstdint>

#include "Constraint.h"
#include "FullColumn.h"
#include "enum.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void Constraint::initialize()
{
    Item::initialize();
    aConstant = 0.0;
}

void Constraint::postInput()
{
    lam = 0.0;
    Item::postInput();
}

void Constraint::prePosIC()
{
    lam = 0.0;
    iG = SIZE_MAX;
    Item::prePosIC();
}

void Constraint::prePosKine()
{
    //"Preserve lam calculated from AccIC for possible use by DynIntegrator if system is not kinematic."
    auto lamOld = lam;
    prePosIC();
    lam = lamOld;
}

void Constraint::fillEssenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    if (type() == essential) {
        essenConstraints->push_back(sptr);
    }
}

void Constraint::fillDispConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
    if (type() == displacement) {
        dispConstraints->push_back(sptr);
    }
}

void Constraint::fillPerpenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
    if (type() == perpendicular) {
        perpenConstraints->push_back(sptr);
    }
}

void Constraint::fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    if (type() == redundant) {
        redunConstraints->push_back(sptr);
    }
}

void Constraint::fillConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    allConstraints->push_back(sptr);
}

ConstraintType Constraint::type()
{
    return essential;
}

void Constraint::setpqsumu(FColDsptr col)
{
    mu = col->at(iG);
}

void Constraint::setpqsumudot(FColDsptr col)
{
    lam = col->at(iG);
}

void Constraint::setpqsumuddot(FColDsptr col)
{
    //Do nothing
}

void Constraint::fillDynError(FColDsptr col)
{
    //"Same as fillPosICError: col."
    fillPosICError(col);
}

void Constraint::fillqsulam(FColDsptr col)
{
    col->atiput(iG, lam);
}

void Constraint::fillpqsumu(FColDsptr col)
{
    col->atiput(iG, mu);
}

void Constraint::fillpqsumudot(FColDsptr col)
{
    col->atiput(iG, lam);
}

void Constraint::setqsulam(FColDsptr col)
{
    lam = col->at(iG);
}

void Constraint::setqsudotlam(FColDsptr col)
{
    lam = col->at(iG);
}

void Constraint::fillPosICError(FColDsptr col)
{
    col->atiplusNumber(iG, aG);
}

void Constraint::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>>)
{
    //My owner should handle this.
    throw SimulationStoppingError("To be implemented.");
}

void Constraint::setConstant(double value)
{
    aConstant = value;
}

void Constraint::reactivateRedundantConstraints()
{
    //My owner should handle this.
    throw SimulationStoppingError("To be implemented.");
}

bool Constraint::isRedundant()
{
    return false;
}

void Constraint::preDyn()
{
    mu = 0.0;
}

void Constraint::fillPosKineError(FColDsptr col)
{
    col->atiplusNumber(iG, aG);
}

void Constraint::fillqsuddotlam(FColDsptr col)
{
    col->atiput(iG, lam);
}

void Constraint::preAccIC()
{
    lam = 0.0;
    Item::preAccIC();
}

void Constraint::fillAccICIterJacob(SpMatDsptr mat)
{
    //"Same as velIC."
    fillVelICJacob(mat);
}

void Constraint::setqsuddotlam(FColDsptr col)
{
    lam = col->at(iG);
}

void Constraint::addToJointForceI(FColDsptr)
{
    //Do nothing.
}

void Constraint::addToJointTorqueI(FColDsptr)
{
    //Do nothing.
}

void Constraint::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) {
    Item::fillConstraints(allConstraints);
}

void Constraint::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) {
    Item::fillRedundantConstraints(redunConstraints);
}

void Constraint::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints) {
    Item::fillDispConstraints(dispConstraints);
}

void Constraint::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) {
    Item::fillEssenConstraints(essenConstraints);
}

void Constraint::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints) {
    Item::fillPerpenConstraints(perpenConstraints);
}
