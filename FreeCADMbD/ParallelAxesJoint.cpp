/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ParallelAxesJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<ParallelAxesJoint> ParallelAxesJoint::With()
{
    auto inst = std::make_shared<ParallelAxesJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ParallelAxesJoint> ParallelAxesJoint::With(const std::string& str)
{
    auto inst = std::make_shared<ParallelAxesJoint>(str);
    inst->initialize();
    return inst;
}

void ParallelAxesJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
