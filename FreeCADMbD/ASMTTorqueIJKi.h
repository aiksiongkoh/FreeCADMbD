/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJKi.h"

namespace MbD {
    class ASMTTorqueIJKi : public ASMTSymbolicFunctionIJKi
    {
        //
    public:
        static std::shared_ptr<ASMTTorqueIJKi> With();
        std::shared_ptr<KinematicIJ> mbdClassNew() override;
        double asmtUnit() override;

    };
}
