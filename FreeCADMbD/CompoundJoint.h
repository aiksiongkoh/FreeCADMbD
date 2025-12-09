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
    class CompoundJoint : public JointIJ
    {
        //distanceIJ
    public:
        CompoundJoint() {}
        CompoundJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<CompoundJoint> With();
        static std::shared_ptr<CompoundJoint> With(const std::string& str);

        double distanceIJ = 0.0;
    };
}


