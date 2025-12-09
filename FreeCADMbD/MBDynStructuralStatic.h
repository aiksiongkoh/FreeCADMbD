/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynStructural.h"

namespace MbD {
    class MBDynStructuralStatic : public MBDynStructural
    {
    public:
        MBDynStructuralStatic() {}
        static std::shared_ptr<MBDynStructuralStatic> With();

        void parseMBDyn(std::string line) override;

    };
};
