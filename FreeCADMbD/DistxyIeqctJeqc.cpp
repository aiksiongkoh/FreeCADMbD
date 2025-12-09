/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIeqctJeqc.h"

using namespace MbD;

std::shared_ptr<DistxyIeqctJeqc> DistxyIeqctJeqc::With()
{
    auto inst = std::make_shared<DistxyIeqctJeqc>();
    inst->initialize();
    return inst;
}
