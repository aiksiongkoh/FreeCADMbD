/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynControlData.h"

namespace MbD {
    class MBDynOutputMeter : public MBDynControlData
    {
    public:
        static std::shared_ptr<MBDynOutputMeter> With();

        void parseMBDyn(std::string line) override;
        void readFunction(std::vector<std::string>& args) override;

        std::string outputMeterString, outputMeterName, formula;

    };
}
