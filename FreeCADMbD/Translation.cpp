/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Translation.h"
#include "System.h"
#include "SimulationStoppingError.h"

using namespace MbD;

Translation::Translation(const std::string&)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<Translation> Translation::With(const std::string& str)
{
    auto inst = std::make_shared<Translation>();
    inst->initialize();
    return inst;
}

void Translation::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 0));
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 1));
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 2));
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}
