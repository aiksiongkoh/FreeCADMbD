/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynDrive.h"

namespace MbD {
    class MBDynDriveElement : public MBDynDrive
    {
    public:
        static std::shared_ptr<MBDynDriveElement> With();

        void readFunction(std::vector<std::string>& args) override;
        void createASMT() override;

        std::string elementLabel, elementType, str, component, direct, output, yesno;
    };
}
