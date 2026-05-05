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
    class DispIeJeKeq : public DispIeJeKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeJeKeq() {}
        DispIeJeKeq(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeKe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpEK() override;
        void calcppVectorpEKpEK() override;
        FMatDsptr getpVectorpEK();
        FMatFColDsptr getppVectorpEKpEK();
        FMatDsptr getppCompipEIpEI(size_t axis) override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FMatDsptr prIeJeKepEK;
        FMatFColDsptr pprIeJeKepEKpEK;

    };
}

