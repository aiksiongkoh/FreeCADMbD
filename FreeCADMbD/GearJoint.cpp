/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearJoint.h"
#include "GearConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<GearJoint> GearJoint::With()
{
    auto inst = std::make_shared<GearJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<GearJoint> GearJoint::With(const std::string& str)
{
    auto inst = std::make_shared<GearJoint>(str);
    inst->initialize();
    return inst;
}

void GearJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        auto gearIJ = GearConstraintIJ::With(eFrmI, eFrmJ);
        gearIJ->radiusI = radiusI;
        gearIJ->radiusJ = radiusJ;
        gearIJ->setConstant(std::numeric_limits<double>::min());
        addConstraint(gearIJ);
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
