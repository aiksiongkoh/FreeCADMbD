/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeJeKe.h"

namespace MbD {
    class DispIeJeqKe : public DispIeJeKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeJeqKe() {}
        DispIeJeqKe(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeKe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXJ() override;
        void calcpVectorpEJ() override;
        void calcppVectorpEJpEJ() override;
        FMatDsptr getprIeJeKepXJ() override;
        FMatDsptr getprIeJeKepEJ() override;
        FMatDsptr getppriIeJeKepEJpEJ(size_t axis) override;
        FMatDsptr prIeJeKepXJ;
        FMatDsptr prIeJeKepEJ;
        FMatFColDsptr pprIeJeKepEJpEJ;

    };
}

