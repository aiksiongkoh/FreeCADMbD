/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTRefItem.h"

namespace MbD {
    class ASMTRefPoint : public ASMTRefItem
    {
        //
    public:
        static std::shared_ptr<ASMTRefPoint> With();

        void parseASMT(std::vector<std::string>& lines) override;
        std::string fullName(const std::string& partialName) override;
        void createMbD() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;

    
    };
}

