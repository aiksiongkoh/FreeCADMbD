/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationLimitIJ.h"
#include "TranslationConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<TranslationLimitIJ> TranslationLimitIJ::With()
{
    auto translationLimit = std::make_shared<TranslationLimitIJ>();
    translationLimit->initialize();
    return translationLimit;
}

void TranslationLimitIJ::initializeGlobally()
{
    if (constraints->empty()) {
        auto transConIJ = TranslationConstraintIJ::With(eFrmI, eFrmJ, 2);
        transConIJ->setConstant(limit);
        addConstraint(transConIJ);
        this->root()->hasChanged = true;
    }
    else {
        LimitIJ::initializeGlobally();
    }
}
