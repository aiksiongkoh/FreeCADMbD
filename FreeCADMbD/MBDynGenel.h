/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynElement.h"

namespace MbD {
    class MBDynGenel : public MBDynElement
    {
    public:
        static std::shared_ptr<MBDynGenel> newGenel(std::string line);
        void parseMBDyn(std::string line) override;
        void createASMT() override;

        std::string genelString, type, nodeName, valueType, formula;
    };

}