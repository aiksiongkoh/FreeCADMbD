/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AccICNewtonRaphson.h"

namespace MbD {
    class AccICKineNewtonRaphson : public AccICNewtonRaphson
    {
        //Kinematics with under constrained system
    public:
        static std::shared_ptr<AccICKineNewtonRaphson> With();

        void run() override;
        void iterate() override;
        void initializeGlobally() override;
        void preRun() override;


    };
}

