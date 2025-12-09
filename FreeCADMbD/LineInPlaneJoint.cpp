/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "LineInPlaneJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<LineInPlaneJoint> LineInPlaneJoint::With()
{
    auto inst = std::make_shared<LineInPlaneJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<LineInPlaneJoint> LineInPlaneJoint::With(const std::string& str)
{
    auto inst = std::make_shared<LineInPlaneJoint>(str);
    inst->initialize();
    return inst;
}

void LineInPlaneJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createInPlaneConstraint();
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 2));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
