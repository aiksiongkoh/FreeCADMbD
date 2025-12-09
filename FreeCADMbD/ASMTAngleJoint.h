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
    class ASMTAngleJoint : public ASMTJoint
    {
        //
    public:
        ASMTAngleJoint() {}
		ASMTAngleJoint(const std::string& str) {}
        static std::shared_ptr<ASMTAngleJoint> With();
        static std::shared_ptr<ASMTAngleJoint> With(const std::string& str);

        std::shared_ptr<ConstraintSet> mbdClassNew() override;
        void parseASMT(std::vector<std::string>& lines) override;
        void readTheIzJz(std::vector<std::string>& lines);
        void createMbD() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;

        double theIzJz = 0.0;
    };
}

