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
    class ForceBasicqcsComp : public ForceBasicqcComp
    {
        //  
    public:
        static std::shared_ptr<ForceBasicqcsComp> With();
    };
}
