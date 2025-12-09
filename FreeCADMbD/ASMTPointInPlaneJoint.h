/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTInPlaneJoint.h"

namespace MbD {
    class ASMTPointInPlaneJoint : public ASMTInPlaneJoint
    {
        //
    public:
        static std::shared_ptr<ASMTPointInPlaneJoint> With();
        std::shared_ptr<ConstraintSet> mbdClassNew() override;
        void parseASMT(std::vector<std::string>& lines) override;
        void readOffset(std::vector<std::string>& lines);
        void createMbD() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
    };
}

