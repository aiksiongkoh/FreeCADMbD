/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJKi.h"

namespace MbD {
    class ASMTForceIJKi : public ASMTSymbolicFunctionIJKi
    {
        //
    public:
        static std::shared_ptr<ASMTForceIJKi> With();
        std::shared_ptr<KinematicIJ> mbdClassNew() override;
        double asmtUnit() override;

    };
}
