/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynGenel.h"

namespace MbD {
    class MBDynClampGenel : public MBDynGenel
    {
    public:
        static std::shared_ptr<MBDynClampGenel> With();

        void parseMBDyn(std::string line) override;
        void createASMT() override;
    };

}

