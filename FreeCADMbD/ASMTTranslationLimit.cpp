/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTTranslationLimit.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "TranslationLimitIJ.h"

using namespace MbD;

std::shared_ptr<ASMTTranslationLimit> ASMTTranslationLimit::With()
{
    auto translationLimit = std::make_shared<ASMTTranslationLimit>();
    translationLimit->initialize();
    return translationLimit;
}

std::shared_ptr<ConstraintSet> ASMTTranslationLimit::mbdClassNew()
{
    return TranslationLimitIJ::With();
}

void ASMTTranslationLimit::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "TranslationLimit");
    ASMTLimit::storeOnLevel(os, level);
}
