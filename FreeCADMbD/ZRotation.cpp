/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "System.h"
#include "ZRotation.h"
#include "FullColumn.h"
#include "DirectionCosineConstraintIJ.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<ZRotation> ZRotation::With()
{
    auto inst = std::make_shared<ZRotation>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ZRotation> ZRotation::With(const std::string& str)
{
    auto inst = std::make_shared<ZRotation>(str);
    inst->initialize();
    return inst;
}

void ZRotation::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        auto dirCosCon = DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 1, 0);
        addConstraint(dirCosCon);
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}
