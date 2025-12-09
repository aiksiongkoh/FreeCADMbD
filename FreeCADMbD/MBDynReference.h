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

    class MBDynReference : public MBDynItem
    {
    public:
        static std::shared_ptr<MBDynReference> With();
        void initialize() override;

        void parseMBDyn(std::string line) override;
        void readPosition(std::vector<std::string>& args);
        void readOrientation(std::vector<std::string>& args);
        void readVelocity(std::vector<std::string>& args);
        void readOmega(std::vector<std::string>& args);

        std::string refString, baseRefName;
        FColDsptr rFfF, vFfF, omeFfF;
        FMatDsptr aAFf;
    };
}
