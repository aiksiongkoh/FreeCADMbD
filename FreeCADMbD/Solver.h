/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <string>
#include <memory>

#include "Numeric.h"
#include "SolverStatistics.h"

namespace MbD {
    class Solver : public Numeric
    {
        //statistics
    public:
        //virtual ~Solver() {}
        static std::shared_ptr<Solver> With();
        virtual void initialize();

        void noop();
        virtual void initializeLocally();
        virtual void initializeGlobally();
        virtual void assignEquationNumbers();
        virtual void run() = 0;
        virtual void preRun();
        virtual void finalize();
        virtual void reportStats();
        virtual void postRun();
        virtual void logString(const std::string& str);
        virtual void setSystem(Solver* sys);
        virtual void handleSingularMatrix();

        std::shared_ptr<SolverStatistics> statistics = std::make_shared<SolverStatistics>();
    };
}

