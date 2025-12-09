/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

//Use SymTime instead of Time since Time.h is too common.
 
#pragma once

#include "IndependentVariable.h"

namespace MbD {
    class SymTime : public IndependentVariable
    {
    public:
        SymTime();
        void initialize() override;
    };
}

