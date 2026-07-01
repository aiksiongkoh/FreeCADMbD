/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationalJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIeJe.h"
#include "TranslationConstraintIeJe.h"

using namespace MbD;

std::shared_ptr<TranslationalJoint> TranslationalJoint::With()
{
    auto inst = std::make_shared<TranslationalJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<TranslationalJoint> TranslationalJoint::With(const std::string& str)
{
    auto inst = std::make_shared<TranslationalJoint>(str);
    inst->initialize();
    return inst;
}

void TranslationalJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        createInLineConstraints();
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 1, 0));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}

void MbD::TranslationalJoint::preAccIC()
{
        InLineJoint::preAccIC();
}
