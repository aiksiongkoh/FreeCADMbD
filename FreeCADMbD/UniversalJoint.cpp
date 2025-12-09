/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "UniversalJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<UniversalJoint> UniversalJoint::With()
{
    auto inst = std::make_shared<UniversalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<UniversalJoint> UniversalJoint::With(const std::string& str)
{
    auto inst = std::make_shared<UniversalJoint>(str);
    inst->initialize();
    return inst;
}

void UniversalJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createAtPointConstraints();
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 2));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
