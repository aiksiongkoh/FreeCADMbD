/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "SystemNewtonRaphson.h"

namespace MbD {
    class PosNewtonRaphson : public SystemNewtonRaphson
    {
        //
    public:
        static std::shared_ptr<PosNewtonRaphson> With();

        void preRun() override;
        void incrementIterNo() override;
        void askSystemToUpdate() override;
        void postRun() override;
        virtual void run() = 0;
        void iterate() override;
    };
}

