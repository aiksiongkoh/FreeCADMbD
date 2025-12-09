/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueAction.h"

namespace MbD {
    class ForceTorqueActionComp : public ForceTorqueAction
    {
        //
    public:
        static std::shared_ptr<ForceTorqueActionComp> With();

        size_t axis = SIZE_MAX;
    };
}
