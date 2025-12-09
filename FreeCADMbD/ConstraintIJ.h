/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Constraint.h"
#include "EndFrameqc.h"
 //#include "EndFramec.h"  //EndFrmsptr is defined

namespace MbD {
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;
    
    class ConstraintIJ : public Constraint
    {
    public:
        ConstraintIJ() {}
        ConstraintIJ(const std::string& str) : Constraint(str) {}
        ConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : eFrmI(frmi), eFrmJ(frmj), Constraint() {}
        static std::shared_ptr<ConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;
        EndFrmsptr geteFrmI() override { return eFrmI; }
        EndFrmsptr geteFrmJ() override { return eFrmJ; }
        std::string constraintSpec() override;

        EndFrmsptr eFrmI, eFrmJ;
    };
}

