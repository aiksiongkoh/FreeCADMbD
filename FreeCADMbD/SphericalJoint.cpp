/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "SphericalJoint.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<SphericalJoint> SphericalJoint::With()
{
    auto inst = std::make_shared<SphericalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<SphericalJoint> SphericalJoint::With(const std::string& str)
{
    auto inst = std::make_shared<SphericalJoint>(str);
    inst->initialize();
    return inst;
}

void SphericalJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createAtPointConstraints();
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
