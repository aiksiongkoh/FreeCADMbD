/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceBasicqcVector.h"

namespace MbD {
    class ForceBasicqcsVector : public ForceBasicqcVector
    {
        //
    public:
        static std::shared_ptr<ForceBasicqcsVector> With();

    };
}
