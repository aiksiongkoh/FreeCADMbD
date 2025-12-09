/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTConstraintSet.h"

namespace MbD {
    class ForceTorqueData;

    class ASMTContact : public ASMTConstraintSet
    {
        //
    public:
        static std::shared_ptr<ASMTContact> With();
        void readJointSeries(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        void createMbD() override;

        std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueData>>> jointSeries;

    };
}
