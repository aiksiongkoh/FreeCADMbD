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
    class NoRotationJoint : public JointIJ
    {
        //
    public:
        NoRotationJoint() {}
        NoRotationJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<NoRotationJoint> With();
        static std::shared_ptr<NoRotationJoint> With(const std::string& str);

        void initializeGlobally() override;

    };
}

