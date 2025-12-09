/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RevoluteJoint.h"
#include "System.h"
#include "AtPointConstraintIJ.h"
#include "DirectionCosineConstraintIJ.h"

using namespace MbD;

std::shared_ptr<RevoluteJoint> RevoluteJoint::With()
{
    auto inst = std::make_shared<RevoluteJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RevoluteJoint> RevoluteJoint::With(const std::string& str)
{
    auto inst = std::make_shared<RevoluteJoint>(str);
    inst->initialize();
    return inst;
}

void RevoluteJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createAtPointConstraints();
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
