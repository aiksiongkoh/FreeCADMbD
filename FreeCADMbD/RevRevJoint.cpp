/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "RevRevJoint.h"
#include "DirectionCosineConstraintIeJe.h"
#include "DistancexyConstraintIeJe.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<RevRevJoint> RevRevJoint::With()
{
    auto inst = std::make_shared<RevRevJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RevRevJoint> RevRevJoint::With(const std::string& str)
{
    auto inst = std::make_shared<RevRevJoint>(str);
    inst->initialize();
    return inst;
}

void RevRevJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        auto distxyIJ = DistancexyConstraintIeJe::With(eFrmI, eFrmJ);
        distxyIJ->setConstant(distanceIJ);
        addConstraint(distxyIJ);
        addConstraint(TranslationConstraintIeJe::With(eFrmI, eFrmJ, 2));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        CompoundJoint::initializeGlobally();
    }
}
