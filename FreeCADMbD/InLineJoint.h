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
    class InLineJoint : public JointIJ
    {
        //Abstract class. Create subclasses only.
    public:
        InLineJoint() {}
        InLineJoint(const std::string& str) : JointIJ(str) {}
        
        virtual void initializeGlobally();

        void createInLineConstraints();

    };
}

