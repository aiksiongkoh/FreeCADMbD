/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AtPointJoint.h"

namespace MbD {
    class ConstantVelocityJoint : public AtPointJoint
    {
        //
    public:
        ConstantVelocityJoint() {}
        ConstantVelocityJoint(const std::string& str) : AtPointJoint(str) {}
        static std::shared_ptr<ConstantVelocityJoint> With();
        static std::shared_ptr<ConstantVelocityJoint> With(const std::string& str);
        
        void initializeGlobally() override;
        void connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj) override;


    };
}

