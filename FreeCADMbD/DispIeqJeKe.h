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
        DispIeqJeKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : DispIeJeKe(frmi, frmj, frmk) {}
        static std::shared_ptr<DispIeqJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXI() override;
        void calcpVectorpEI() override;
        void calcppVectorpEIpEI() override;
        FMatDsptr getpVectorpXI() override;
        FMatDsptr getpVectorpEI() override;
        FMatFColDsptr getppVectorpEIpEI() override;
        FMatDsptr getppCompipEIpEI(size_t axis) override;
        FMatDsptr prIeJeKepXI;
        FMatDsptr prIeJeKepEI;
        FMatFColDsptr pprIeJeKepEIpEI;

    };
}

