/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynItem.h"

namespace MbD {

    class MBDynScalarFunction : public MBDynItem
    {
    public:
        static std::shared_ptr<MBDynScalarFunction> With();

        void parseMBDyn(std::string line) override;
        void readFunction(std::vector<std::string>& args) override;
        void createASMT() override;

        std::string scalarFunctionString, scalarFunctionName, formula;
    };
}

