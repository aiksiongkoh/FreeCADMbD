/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceBasicqcComp.h"

namespace MbD {
    class ForceBasicqccqComp : public ForceBasicqcComp
    {
        //iqXaxis prOeOaxispET  
    public:
        static std::shared_ptr<ForceBasicqccqComp> With();
    };
}
