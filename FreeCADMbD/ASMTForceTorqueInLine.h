/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTForceTorque.h"

namespace MbD {
    class ASMTForceTorqueInLine : public ASMTForceTorque
    {
        //
    public:
        static std::shared_ptr<ASMTForceTorqueInLine> With();

        void parseASMT(std::vector<std::string>& lines) override;
        void readTension(std::vector<std::string>& lines);
        void readTwist(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        void createMbD() override;

        std::string tensionFunc, twistFunc;
    };
}

