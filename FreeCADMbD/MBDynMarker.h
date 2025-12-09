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

    class MBDynMarker : public MBDynItem
    {
    public:
        static std::shared_ptr<MBDynMarker> With();
        void initialize() override;

        void parseMBDyn(std::vector<std::string>& args) override;
        void parseMBDynTotalJointMarker(std::vector<std::string>& args);
        void parseMBDynClamp(std::vector<std::string>& args);
        void createASMT() override;
        FColDsptr rOmO();

        std::string nodeStr;
        FColDsptr rPmP; //part to marker
        FMatDsptr aAPm, aAPm2;
    };
}
