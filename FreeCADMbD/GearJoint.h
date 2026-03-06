/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "JointIJ.h"

namespace MbD {
    class GearJoint : public JointIJ
    {
        //radiusI radiusJ aConstant 
    public:
        GearJoint() {}
        GearJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<GearJoint> With();
        static std::shared_ptr<GearJoint> With(const std::string& str);
        
        void initializeGlobally() override;

        double radiusI = std::numeric_limits<double>::min();
        double radiusJ = std::numeric_limits<double>::min();
        double aConstant = std::numeric_limits<double>::min();
    };
}

