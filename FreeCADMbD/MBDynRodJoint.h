/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynJoint.h"

namespace MbD {
    class MBDynRodJoint : public MBDynJoint
    {
    public:
        static std::shared_ptr<MBDynRodJoint> With();

        void parseMBDyn(std::string line) override;
        void readMarkerI(std::vector<std::string>& args) override;
        void readMarkerJ(std::vector<std::string>& args) override;
        void readRodLength(std::vector<std::string>& args);
        void readConstitutiveLaw(std::vector<std::string>& args);
        void createASMT() override;

        double rodLength, stiffness;
    };
}
