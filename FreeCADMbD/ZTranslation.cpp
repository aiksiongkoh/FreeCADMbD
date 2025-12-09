/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ZTranslation.h"
#include "System.h"
#include "SimulationStoppingError.h"

using namespace MbD;

ZTranslation::ZTranslation(const std::string&)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ZTranslation> ZTranslation::With()
{
    auto inst = std::make_shared<ZTranslation>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ZTranslation> ZTranslation::With(const std::string& str)
{
    auto inst = std::make_shared<ZTranslation>(str);
    inst->initialize();
    return inst;
}

void ZTranslation::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        auto tranCon = TranslationConstraintIJ::With(eFrmI, eFrmJ, 2);
        addConstraint(tranCon);
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}
