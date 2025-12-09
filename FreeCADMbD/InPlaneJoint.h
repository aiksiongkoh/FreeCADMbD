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
    class InPlaneJoint : public JointIJ
    {
        //offset
    public:
        InPlaneJoint() {}
        InPlaneJoint(const std::string& str) : JointIJ(str) {}
        
        virtual void initializeGlobally();

        void createInPlaneConstraint();

        double offset = 0.0;
    };
}

