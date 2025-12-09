/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CylSphJoint.h"
#include "DistancexyConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<CylSphJoint> CylSphJoint::With()
{
    auto inst = std::make_shared<CylSphJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<CylSphJoint> CylSphJoint::With(const std::string& str)
{
    auto inst = std::make_shared<CylSphJoint>(str);
    inst->initialize();
    return inst;
}

void CylSphJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        auto distxyIJ = DistancexyConstraintIJ::With(eFrmI, eFrmJ);
        distxyIJ->setConstant(distanceIJ);
        addConstraint(distxyIJ);
        root()->hasChanged = true;
    }
    else {
        CompoundJoint::initializeGlobally();
    }
}
