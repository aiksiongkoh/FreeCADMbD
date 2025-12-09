/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <vector>

#include "IntegratorInterface.h"
#include "enum.h"

namespace MbD {
    class QuasiIntegrator : public IntegratorInterface
    {
        //
    public:
        static std::shared_ptr<QuasiIntegrator> With();
        void initialize() override;

        void preRun() override;
        void run() override;
        void reportStats() override;
        void preFirstStep() override;
        void postFirstStep() override;
        void preStep() override;
        void checkForDiscontinuity() override;
        double suggestSmallerOrAcceptFirstStepSize(double hnew) override;
        double suggestSmallerOrAcceptStepSize(double hnew) override;
        void incrementTime(double tnew) override;
        void throwDiscontinuityError(const std::string& str, std::shared_ptr<std::vector<DiscontinuityType>> discontinuityTypes);
        void checkForOutputThrough(double t) override;
        void interpolateAt(double t) override;
        void postStep() override;
        void postRun() override;
        virtual void useTrialStepStats(std::shared_ptr<SolverStatistics> stats);
        void useQuasiStepStats(std::shared_ptr<SolverStatistics> stats) override;

    };
}

