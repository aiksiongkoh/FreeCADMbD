/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTJoint.h"

namespace MbD {
    class ASMTInPlaneJoint : public ASMTJoint
    {
        //
    public:
        static std::shared_ptr<ASMTInPlaneJoint> With();
        
        void parseASMT(std::vector<std::string>& lines) override;
        void readOffset(std::vector<std::string>& lines);
        void createMbD() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;

        double offset = 0.0;

    };
}
