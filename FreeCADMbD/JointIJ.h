/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <memory>
//#include <vector>
//#include <functional>

#include "Item.h"
#include "EndFrameqc.h"
#include "TranslationConstraintIJ.h"
#include "DirectionCosineConstraintIJ.h"
#include "ConstraintSet.h"

namespace MbD {
    class Constraint;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class JointIJ : public ConstraintSet
    {
        //eFrmI eFrmJ constraints friction 
    public:
        JointIJ() {}
        JointIJ(const std::string& str) : ConstraintSet(str) {}
        JointIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintSet(frmi, frmj) {}
        static std::shared_ptr<JointIJ> With();
        static std::shared_ptr<JointIJ> With(const std::string& str);

    };
}

