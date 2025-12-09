/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynJoint.h"

namespace MbD {
    class ASMTJoint;

    class MBDynInLineJoint : public MBDynJoint
    {
    public:
        static std::shared_ptr<MBDynInLineJoint> With();

        void parseMBDyn(std::string line) override;
        void createASMT() override;
    };
}
