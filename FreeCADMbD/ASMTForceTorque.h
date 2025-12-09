/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTItemIJ.h"

namespace MbD {
    class ForceFunctionParser;

    class ASMTForceTorque : public ASMTItemIJ
    {
        //
    public:
        static std::shared_ptr<ASMTForceTorque> With();

        void updateFromMbD() override;
        void compareResults(AnalysisType type) override;
        void outputResults(AnalysisType type) override;
        void readForceTorqueSeries(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        void createMbD() override;
        std::shared_ptr<ForceFunctionParser> functionParser();
        bool isForceTorque() override;
        std::shared_ptr<StateData> dataFromMbD() override;

    };
}

