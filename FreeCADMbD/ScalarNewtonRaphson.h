/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "NewtonRaphson.h"

namespace MbD {
    class ScalarNewtonRaphson : public NewtonRaphson
    {
        //
    public:
        static std::shared_ptr<ScalarNewtonRaphson> With();

        void initializeGlobally() override;
        void fillY() override;
        void fillPyPx() override;
        void calcyNorm() override;
        void solveEquations() override;
        void updatexold() override;
        void calcdxNorm() override;
        void xEqualxoldPlusdx() override;
        void passRootToSystem() override;

        double xold = 0.0, x = 0.0, dx = 0.0, y = 0.0;
        double pypx = 0.0;

    };
}

