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
    class ASMTForceTorqueGeneral : public ASMTForceTorque
    {
        //markerK aFIeKe aTIeKe 
    public:
        static std::shared_ptr<ASMTForceTorqueGeneral> With();
        void initialize() override;

        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        void createMbD() override;
        void parseASMT(std::vector<std::string>& lines) override;
        void readFxOnI(std::vector<std::string>& lines);
        void readFyOnI(std::vector<std::string>& lines);
        void readFzOnI(std::vector<std::string>& lines);
        void readTxOnI(std::vector<std::string>& lines);
        void readTyOnI(std::vector<std::string>& lines);
        void readTzOnI(std::vector<std::string>& lines);
        void readMarkerKSign(std::vector<std::string>& lines);

        std::string markerKSign;
        std::shared_ptr<ASMTMarker> markerK;
        FColsptr<std::string> aFIeKe, aTIeKe;
    };
}

