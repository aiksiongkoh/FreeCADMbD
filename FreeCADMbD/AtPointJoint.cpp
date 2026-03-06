/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointJoint.h"
#include "System.h"
#include "AtPointConstraintIeJe.h"

using namespace MbD;

std::shared_ptr<AtPointJoint> AtPointJoint::With()
{
    auto inst = std::make_shared<AtPointJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AtPointJoint> AtPointJoint::With(const std::string& str)
{
    auto inst = std::make_shared<AtPointJoint>(str);
    inst->initialize();
    return inst;
}

void AtPointJoint::createAtPointConstraints()
{
    addConstraint(AtPointConstraintIeJe::With(eFrmI, eFrmJ, 0));
    addConstraint(AtPointConstraintIeJe::With(eFrmI, eFrmJ, 1));
    addConstraint(AtPointConstraintIeJe::With(eFrmI, eFrmJ, 2));
}
