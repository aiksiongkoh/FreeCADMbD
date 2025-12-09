/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynElement.h"

namespace MbD {
    class MBDynPlugin : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynPlugin> newPlugin(std::string line);
        void parseMBDyn(std::string line) override;
        void createASMT() override;
 
        std::string pluginString;
    };

}