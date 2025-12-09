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
    class MBDynDrive : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynDrive> newDrive(std::string line);
        void parseMBDyn(std::string line) override;
        void readFunction(std::vector<std::string>& args) override;
        void readDriveElement(std::vector<std::string>& args);
        void createASMT() override;

        std::string driveString, driveName, formula;

    };
}

