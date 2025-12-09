/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTSymbolicFunction.h"
#include "System.h"
#include "Units.h"

namespace MbD {
    class ASMTTime : public ASMTSymbolicFunction
    {
        //
    public:
        static std::shared_ptr<ASMTTime> With();
        
        void deleteMbD();
        void createMbD() override;
        Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
        bool isVariable() override;
        void setValue(double val) override;
        double getValue() override;
        const std::string& getName() const override;

        std::string name = "time";
    };
}

