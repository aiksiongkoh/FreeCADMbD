/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AccNewtonRaphson.h"

namespace MbD {
    class AccKineNewtonRaphson : public AccNewtonRaphson
    {
        //Kinematics with fully constrained system
    public:
        static std::shared_ptr<AccKineNewtonRaphson> With();

        void run() override;
        void iterate() override;
        void initializeGlobally() override;
        void preRun() override;


    };
}

