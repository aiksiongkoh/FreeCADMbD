/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeKe.h"

namespace MbD {
    class DispIeqJeKeq : public DispIeqJeKe
    {
        //prIeJeOpXI prIeJeOpEI pprIeJeOpEIpEI 
    public:
        DispIeqJeKeq() {}
        DispIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeKe(frmi, frmj) {}
        DispIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : DispIeqJeKe(frmi, frmj, frmk) {}
        static std::shared_ptr<DispIeqJeKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpEK() override;
        void calcppVectorpEKpEK() override;
        void calcppVectorpXIpEK() override;
        void calcppVectorpEIpEK() override;
        FMatDsptr getpVectorpEK() override;
        FMatFColDsptr getppVectorpXIpEK() override;
        FMatFColDsptr getppVectorpEIpEK() override;
        FMatFColDsptr getppVectorpEKpEK() override;
        FMatDsptr prIeJeKepEK;
        FMatFColDsptr pprIeJeKepXIpEK;
        FMatFColDsptr pprIeJeKepEIpEK;
        FMatFColDsptr pprIeJeKepEKpEK;

    };
}

