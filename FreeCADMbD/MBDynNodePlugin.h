/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynPlugin.h"

namespace MbD {
    class MBDynNodePlugin : public MBDynPlugin
    {
    public:
        static std::shared_ptr<MBDynNodePlugin> With();

        void parseMBDyn(std::string line) override;
        void createASMT() override;

        std::string varName, nodeName, _string;
    };
}