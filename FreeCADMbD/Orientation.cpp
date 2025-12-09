/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Orientation.h"
#include "System.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Orientation::Orientation(const std::string&)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Orientation> Orientation::With(const std::string& str)
{
    auto inst = std::make_shared<Orientation>(str);
    inst->initialize();
    return inst;
}

void Orientation::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 1, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}
