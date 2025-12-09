/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>
#include "enum.h"
#include <string>

//#include "CADSystem.h"
//#include "ASMTAssembly.h"

namespace MbD {
    class CADSystem;
    class ASMTAssembly;
    class System;
    class SolverStatistics;

    class ExternalSystem
    {
        //
    public:
        static std::shared_ptr<ExternalSystem> With();
        void initialize();

        void preMbDrun(std::shared_ptr<System> mbdSys);
        void updateFromMbD();
        void outputFor(AnalysisType type);
        void logString(const std::string& str);
        void logString(double value);
        void runOndselPiston();
        void runPiston();
        void postMbDrun();
        void useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats);
        void useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats);

        CADSystem* cadSystem;
        ASMTAssembly* asmtAssembly;

    };
}

