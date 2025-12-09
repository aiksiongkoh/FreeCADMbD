/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJ.h"

namespace MbD {

    class ASMTrIJ : public ASMTSymbolicFunctionIJ
    {
        //
    public:
        ASMTrIJ() {}
        static std::shared_ptr<ASMTrIJ> With();
        
        std::shared_ptr<KinematicIJ> mbdClassNew() override;
        double asmtUnit() override;

    };
}

