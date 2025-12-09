/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "VelSolver.h"

namespace MbD {
    class VelKineSolver : public VelSolver
    {
        //Kinematics with fully constrained system
    public:
        static std::shared_ptr<VelKineSolver> With();

        void assignEquationNumbers() override;
        void run() override;
        void outputSpreadsheet();

    };
}

