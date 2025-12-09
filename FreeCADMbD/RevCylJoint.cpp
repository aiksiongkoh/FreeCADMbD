/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RevCylJoint.h"
#include "DistancexyConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<RevCylJoint> RevCylJoint::With()
{
    auto inst = std::make_shared<RevCylJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RevCylJoint> RevCylJoint::With(const std::string& str)
{
    auto inst = std::make_shared<RevCylJoint>(str);
    inst->initialize();
    return inst;
}

void RevCylJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        auto distxyIJ = DistancexyConstraintIJ::With(eFrmI, eFrmJ);
        distxyIJ->setConstant(distanceIJ);
        addConstraint(distxyIJ);
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        CompoundJoint::initializeGlobally();
    }
}
