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
    class MBDynGravity : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynGravity> With();

        void parseMBDyn(std::string line) override;
        void readFunction(std::vector<std::string>& args) override;
        void createASMT() override;

        std::string gravityString, formula;
        FColDsptr gvec;

    };
}
