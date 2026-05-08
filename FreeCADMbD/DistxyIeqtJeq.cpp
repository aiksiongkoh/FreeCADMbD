/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIeqtJeq.h"

using namespace MbD;

std::shared_ptr<DistxyIeqtJeq> DistxyIeqtJeq::With()
{
    auto inst = std::make_shared<DistxyIeqtJeq>();
    inst->initialize();
    return inst;
}
