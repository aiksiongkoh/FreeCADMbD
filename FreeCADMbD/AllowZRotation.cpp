/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "System.h"
#include "AllowZRotation.h"
#include "FullColumn.h"
#include "AllowZRotationConstraintIqctJqc.h"
#include "AllowZRotationConstraintIctJqc.h"
#include "EndFramect.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "RedundantConstraint.h"

using namespace MbD;

AllowZRotation::AllowZRotation(const std::string& str) : PrescribedMotion(str) 
{
    //Do nothing.
}

std::shared_ptr<AllowZRotation> AllowZRotation::With()
{
    auto inst = std::make_shared<AllowZRotation>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AllowZRotation> AllowZRotation::With(const std::string& str)
{
    auto inst = std::make_shared<AllowZRotation>(str);
    inst->initialize();
    return inst;
}

void AllowZRotation::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        std::shared_ptr<Constraint> dirCosCon;
        auto eFrmIct = std::dynamic_pointer_cast<EndFramect>(eFrmI);
        auto eFrmIqct = std::dynamic_pointer_cast<EndFrameqct>(eFrmI);
        if (eFrmIct && !eFrmIqct) {
            dirCosCon = AllowZRotationConstraintIctJqc::With(eFrmI, eFrmJ, 1, 0);
        }
        else if (!eFrmIct && eFrmIqct) {
            dirCosCon = AllowZRotationConstraintIqctJqc::With(eFrmI, eFrmJ, 1, 0);
        }
        else {
            throw SimulationStoppingError("Check this.");
        }
        addConstraint(dirCosCon);
        this->root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}

void AllowZRotation::postPosIC()
{
    for (size_t i = 0; i < constraints->size(); i++)
    {
        auto constraint = constraints->at(i);
        auto redunCon = RedundantConstraint::With();
        redunCon->constraint = constraint;
        constraints->at(i) = redunCon;
    }
}
