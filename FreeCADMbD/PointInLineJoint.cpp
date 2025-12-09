/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PointInLineJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<PointInLineJoint> PointInLineJoint::With()
{
    auto inst = std::make_shared<PointInLineJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<PointInLineJoint> PointInLineJoint::With(const std::string& str)
{
    auto inst = std::make_shared<PointInLineJoint>(str);
    inst->initialize();
    return inst;
}

void PointInLineJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createInLineConstraints();
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
