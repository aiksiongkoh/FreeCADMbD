/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <algorithm>
#include <iterator>

#include "Arguments.h"

using namespace MbD;


std::shared_ptr<Arguments> Arguments::With()
{
    auto inst = std::make_shared<Arguments>();
    inst->initialize();
    return inst;
}

void Arguments::arguments(Symsptr args)
{
    auto arguments = std::static_pointer_cast<Arguments>(args);
    terms = arguments->terms;
}
