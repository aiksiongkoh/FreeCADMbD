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
    class ASMTOmegaIJKi : public ASMTSymbolicFunctionIJKi
    {
        //
    public:
        static std::shared_ptr<ASMTOmegaIJKi> With();
        std::shared_ptr<KinematicIJ> mbdClassNew() override;
        std::shared_ptr<KinematicIJ> mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) override;
        std::shared_ptr<KinematicIJ> mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) override;
        double asmtUnit() override;


    };
}
