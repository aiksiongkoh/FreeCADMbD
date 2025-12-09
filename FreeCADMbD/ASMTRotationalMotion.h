/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTMotion.h"
#include "ZRotation.h"

namespace MbD {
    class ASMTRotationalMotion : public ASMTMotion
    {
        //
    public:
        static std::shared_ptr<ASMTRotationalMotion> With();

        void parseASMT(std::vector<std::string>& lines) override;
        void readMotionJoint(std::vector<std::string>& lines);
        void readRotationZ(std::vector<std::string>& lines);
        void createMbD() override;
        std::shared_ptr<ConstraintSet> mbdClassNew() override;
        void setMotionJoint(std::string motionJoint);
        void setRotationZ(std::string rotZ);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;

        std::string rotationZ;
    };
}

