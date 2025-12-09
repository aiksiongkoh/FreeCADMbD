/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynElement.h"
#include "MBDynMarker.h"

namespace MbD {
    class ASMTJoint;

    class MBDynJoint : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynJoint> newJoint(std::string line);
        void initialize() override;

        void parseMBDyn(std::string line) override;
        virtual void readJointType(std::vector<std::string>& args);
        virtual void readMarkerI(std::vector<std::string>& args);
        virtual void readMarkerJ(std::vector<std::string>& args);
        void readTotalJointMarkerI(std::vector<std::string>& args);
        void readTotalJointMarkerJ(std::vector<std::string>& args);
        void readClampMarkerJ(std::vector<std::string>& args);
        void readFunction(std::vector<std::string>& args) override;
        void readTotalJointFunction(std::vector<std::string>& args);
        void createASMT() override;
        virtual void outputLine(size_t i, std::ostream& os);

        std::string jointString, joint_type, node_1_label, node_2_label;
        std::shared_ptr<MBDynMarker> mkr1, mkr2;
        std::string formula;
    };
}
