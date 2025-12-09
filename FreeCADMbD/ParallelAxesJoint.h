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
    class ParallelAxesJoint : public JointIJ
    {
        //
    public:
        ParallelAxesJoint() {}
        ParallelAxesJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<ParallelAxesJoint> With();
        static std::shared_ptr<ParallelAxesJoint> With(const std::string& str);

        void initializeGlobally() override;

    };
}

