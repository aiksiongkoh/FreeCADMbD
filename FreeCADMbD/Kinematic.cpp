/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "Kinematic.h"

using namespace MbD;

void Kinematic::initialize()
{
    Item::initialize();
}

void Kinematic::useUniqueDispIeJeO()
{
    //Do nothing.
}

void Kinematic::useUniqueDispIeJeKe()
{
    //Do nothing.
}

void Kinematic::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    //Do nothing.
}

void Kinematic::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
    //Do nothing.
}

void Kinematic::constraintsReport()
{
    //Do nothing.
}

void Kinematic::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    //Do nothing.
}

void Kinematic::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    //Do nothing.
}

void Kinematic::reactivateRedundantConstraints()
{
    //Do nothing.
}
