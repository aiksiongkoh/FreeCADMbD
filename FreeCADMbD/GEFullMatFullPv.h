/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "GEFullMat.h"

namespace MbD {
    class GEFullMatFullPv : public GEFullMat
    {
        //
    public:
        static std::shared_ptr<GEFullMatFullPv> With();
        
        void doPivoting(size_t p) override;
        void postSolve() override;
    };
}

