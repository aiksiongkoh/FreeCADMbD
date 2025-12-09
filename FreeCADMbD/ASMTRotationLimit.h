/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTLimit.h"

namespace MbD {
    class ASMTRotationLimit : public ASMTLimit
    {
        //
    public:
        static std::shared_ptr<ASMTRotationLimit> With();
        std::shared_ptr<ConstraintSet> mbdClassNew() override;
        void storeOnLevel(std::ofstream& os, size_t level) override;

    };
}
