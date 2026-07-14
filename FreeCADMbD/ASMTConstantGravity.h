/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTItem.h"
//#include "Units.h"

namespace MbD {
    class System;
    class Units;

    class ASMTConstantGravity : public ASMTItem
    {
        //
    public:
        static std::shared_ptr<ASMTConstantGravity> With();
        void initialize() override;

        void parseASMT(std::vector<std::string>& lines) override;
        void createMbD() override;
        FColDsptr getg() const;
        void setg(FColDsptr g);

        void setg(double a, double b, double c);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        std::string reportComparisonWith(std::shared_ptr<ASMTItem> other) override;

        FColDsptr g = std::make_shared<FullColumn<double>>(ListD{ 0.,0.,0. });
    };
}

