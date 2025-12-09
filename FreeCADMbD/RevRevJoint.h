/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "CompoundJoint.h"

namespace MbD {
    class RevRevJoint : public CompoundJoint
    {
        //
    public:
        RevRevJoint() {}
        RevRevJoint(const std::string& str) : CompoundJoint(str) {}
        static std::shared_ptr<RevRevJoint> With();
        static std::shared_ptr<RevRevJoint> With(const std::string& str);

        void initializeGlobally() override;


    };
}

