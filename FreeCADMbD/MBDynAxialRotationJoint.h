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
    class ASMTRotationalMotion;

    class MBDynAxialRotationJoint : public MBDynJoint
    {
    public:
        static std::shared_ptr<MBDynAxialRotationJoint> With();

        void parseMBDyn(std::string line) override;
        void createASMT() override;
        void outputLine(size_t i, std::ostream& os) override;

        std::shared_ptr<ASMTRotationalMotion> asmtMotion;
    };

}