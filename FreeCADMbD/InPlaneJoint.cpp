/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "InPlaneJoint.h"
#include "TranslationConstraintIeJe.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void InPlaneJoint::initializeGlobally()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void InPlaneJoint::createInPlaneConstraint()
{
    auto tranCon = TranslationConstraintIeJe::With(eFrmI, eFrmJ, 2);
    tranCon->setConstant(offset);
    addConstraint(tranCon);
}
