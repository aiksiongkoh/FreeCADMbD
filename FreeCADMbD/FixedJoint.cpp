/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FixedJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"

using namespace MbD;

std::shared_ptr<FixedJoint> FixedJoint::With()
{
    auto inst = std::make_shared<FixedJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<FixedJoint> FixedJoint::With(const std::string& str)
{
    auto inst = std::make_shared<FixedJoint>(str);
    inst->initialize();
    return inst;
}

void FixedJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createAtPointConstraints();
        //addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 0, 1));
        //addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 1, 2));
        //addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 1, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
