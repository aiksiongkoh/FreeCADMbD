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
    class ScrewJoint : public JointIJ
    {
        //
    public:
        ScrewJoint() {}
        ScrewJoint(const std::string& str) : JointIJ(str) {}
        static std::shared_ptr<ScrewJoint> With();
        static std::shared_ptr<ScrewJoint> With(const std::string& str);

        //void initializeLocally() override;
        void initializeGlobally() override;
        void connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj) override;

        double pitch = 1.0, aConstant = 0.0;
    };
}

