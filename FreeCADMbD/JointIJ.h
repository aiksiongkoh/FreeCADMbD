/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintSet.h"

namespace MbD {
    class Constraint;
    class EndFrame;
    using EndFrmsptr = std::shared_ptr<EndFrame>;

    class JointIJ : public ConstraintSet
    {
    public:
        JointIJ() {}
        JointIJ(const std::string& str) : ConstraintSet(str) {}
        JointIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintSet(frmi, frmj) {}
        static std::shared_ptr<JointIJ> With();
        static std::shared_ptr<JointIJ> With(const std::string& str);

    };
}

