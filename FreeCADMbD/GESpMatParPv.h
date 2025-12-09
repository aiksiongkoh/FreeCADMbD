/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "GESpMat.h"

namespace MbD {
    class GESpMatParPv : public GESpMat
    {
        //
    public:
        static std::shared_ptr<GESpMatParPv> With();

        void forwardEliminateWithPivot(size_t p) override;
        void backSubstituteIntoDU() override;
        void postSolve() override;

    };
}

