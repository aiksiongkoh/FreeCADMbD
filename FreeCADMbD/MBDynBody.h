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
    class MBDynBody : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynBody> With();
        void initialize() override;

        void parseMBDyn(std::string line) override;
        void readMass(std::vector<std::string>& args);
        void readPositionCM(std::vector<std::string>& args);
        void readInertiaMatrix(std::vector<std::string>& args);
        void readOrientationCM(std::vector<std::string>& args);
        void readMassProps(std::vector<std::string>& args);
        void createASMT() override;

        std::string bodyString, nodeName;
        double mass = std::numeric_limits<double>::min();
        FColDsptr rPcmP;
        FMatDsptr aJmat;
        FMatDsptr aAPcm;
        std::shared_ptr<std::vector<double>> masses;
        std::shared_ptr<std::vector<FColDsptr>> rPcmPs;
        std::shared_ptr<std::vector<FMatDsptr>> aJmats;
        std::shared_ptr<std::vector<FMatDsptr>> aAPcms;

    };
}
