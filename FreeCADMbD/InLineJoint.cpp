/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "InLineJoint.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void InLineJoint::initializeGlobally()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void InLineJoint::createInLineConstraints()
{
    addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 0));
    addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 1));
}
