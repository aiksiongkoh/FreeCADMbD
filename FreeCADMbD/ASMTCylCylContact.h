/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTContact.h"

namespace MbD {
    class ASMTCylCylContact : public ASMTContact
    {
        //
    public:
        void parseASMT(std::vector<std::string>& lines) override;
        void readDistanceIJ(std::vector<std::string>& lines);
        void createMbD() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;

        double distancexyIJ = 0.0;

    };
}
