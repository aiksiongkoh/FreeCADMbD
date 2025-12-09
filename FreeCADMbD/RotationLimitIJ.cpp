/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "RotationLimitIJ.h"
#include "AngleZConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<RotationLimitIJ> RotationLimitIJ::With()
{
    auto rotationLimit = std::make_shared<RotationLimitIJ>();
    rotationLimit->initialize();
    return rotationLimit;
}

void RotationLimitIJ::initializeGlobally()
{
    if (constraints->empty()) {
        auto angleZConIJ = AngleZConstraintIJ::With(eFrmI, eFrmJ);
        angleZConIJ->setConstant(limit);
        addConstraint(angleZConIJ);
        this->root()->hasChanged = true;
    }
    else {
        LimitIJ::initializeGlobally();
    }
}
