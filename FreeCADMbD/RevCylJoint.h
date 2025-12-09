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
    class RevCylJoint : public CompoundJoint
    {
        //
    public:
        RevCylJoint() {}
        RevCylJoint(const std::string& str) : CompoundJoint(str) {}
        static std::shared_ptr<RevCylJoint> With();
        static std::shared_ptr<RevCylJoint> With(const std::string& str);

        void initializeGlobally() override;
    

    };
}

