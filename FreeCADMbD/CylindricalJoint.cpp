/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CylindricalJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"
#include "TranslationConstraintIJ.h"

using namespace MbD;

std::shared_ptr<CylindricalJoint> CylindricalJoint::With()
{
    auto inst = std::make_shared<CylindricalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<CylindricalJoint> CylindricalJoint::With(const std::string& str)
{
    auto inst = std::make_shared<CylindricalJoint>(str);
    inst->initialize();
    return inst;
}

void CylindricalJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createInLineConstraints();
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}
