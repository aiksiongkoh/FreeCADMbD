/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJ.h"

namespace MbD {
    class ASMTForceIJ : public ASMTSymbolicFunctionIJ
    {
        //
    public:
        static std::shared_ptr<ASMTForceIJ> With();
        void createMbD() override;
        double asmtUnit() override;

    };
}

