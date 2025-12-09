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
    class AngleJoint : public JointIJ
    {
        //theIzJz
    public:
		AngleJoint() {}
		AngleJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<AngleJoint> With();
        static std::shared_ptr<AngleJoint> With(const std::string& str);

        void initializeGlobally() override;

        double theIzJz = 0.0;
    };
}

