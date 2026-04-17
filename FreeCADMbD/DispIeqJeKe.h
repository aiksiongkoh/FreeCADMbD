/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeJeKe.h"

namespace MbD {
    class DispIeqJeKe : public DispIeJeKe
    {
        //prIeJeOpXI prIeJeOpEI pprIeJeOpEIpEI 
    public:
        DispIeqJeKe() {}
        DispIeqJeKe(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeKe(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXI() override;
        void calcpVectorpEI() override;
        void calcppVectorpEIpEI() override;
        FMatDsptr getprIeJeKepXI() override;
        FMatDsptr getprIeJeKepEI() override;
        FMatDsptr getppriIeJeKepEIpEI(size_t axis) override;
        FMatDsptr prIeJeKepXI;
        FMatDsptr prIeJeKepEI;
        FMatFColDsptr pprIeJeKepEIpEI;

    };
}

