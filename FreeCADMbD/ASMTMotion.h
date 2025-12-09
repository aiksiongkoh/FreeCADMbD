/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTConstraintSet.h"
#include "ForceTorqueData.h"

namespace MbD {
    class ASMTMotion : public ASMTConstraintSet
    {
        //
    public:
        static std::shared_ptr<ASMTMotion> With();
        
        void readMotionSeries(std::vector<std::string>& lines);
        virtual void initMarkers();
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        void createMbD() override;
        bool isMotion() override;

        std::string motionJoint;
        std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueData>>> motionSeries;

    };
}
