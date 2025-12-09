/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTMotion.h"

namespace MbD {
    class ASMTTranslationalMotion : public ASMTMotion
    {
        //
    public:
        static std::shared_ptr<ASMTTranslationalMotion> With();

        void parseASMT(std::vector<std::string>& lines) override;
        void createMbD() override;
        std::shared_ptr<ConstraintSet> mbdClassNew() override;
        void readMotionJoint(std::vector<std::string>& lines);
        void readTranslationZ(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;

        std::string translationZ;

    };
}

