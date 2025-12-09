/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Function.h"
#include "Symbolic.h"
#include "System.h"
#include "Units.h"

namespace MbD {

    class FunctionWithManyArgs : public Function
    {
        //terms
    public:
        FunctionWithManyArgs();
        FunctionWithManyArgs(Symsptr term);
        FunctionWithManyArgs(Symsptr term, Symsptr term1);
        FunctionWithManyArgs(Symsptr term, Symsptr term1, Symsptr term2);
        FunctionWithManyArgs(std::shared_ptr<std::vector<Symsptr>> _terms);
        static std::shared_ptr<FunctionWithManyArgs> With();
        
        std::shared_ptr<std::vector<Symsptr>> getTerms() override;
        void createMbD() override;
        void arguments(Symsptr args) override;
        bool isConstant() override;
        void fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs) override;
        void fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs) override;
        void fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointForces) override;
        void fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointTorques) override;

        std::shared_ptr<std::vector<Symsptr>> terms;
    };
}

