/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PerpendicularJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<PerpendicularJoint> PerpendicularJoint::With()
{
    auto inst = std::make_shared<PerpendicularJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<PerpendicularJoint> PerpendicularJoint::With(const std::string& str)
{
    auto inst = std::make_shared<PerpendicularJoint>(str);
    inst->initialize();
    return inst;
}

void PerpendicularJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 2));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
