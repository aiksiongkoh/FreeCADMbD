/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "FunctionParser.h"

namespace MbD {
    class MotionFunctionParser : public FunctionParser
    {
        //
    public:
        static std::shared_ptr<MotionFunctionParser> With();

    };
}
