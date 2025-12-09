/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "Extrapolator.h"

namespace MbD {
    class Interpolator : public Extrapolator
    {
        //
    public:
        static std::shared_ptr<Interpolator> With();


    };
}
