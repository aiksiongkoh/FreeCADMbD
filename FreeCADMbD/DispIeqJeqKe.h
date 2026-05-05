/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeKe.h"

namespace MbD {
    class DispIeqJeqKe : public DispIeqJeKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqJeqKe() {}
        DispIeqJeqKe(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeKe(frmi, frmj) {}
        DispIeqJeqKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : DispIeqJeKe(frmi, frmj, frmk) {}
        static std::shared_ptr<DispIeqJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXJ() override;
        void calcpVectorpEJ() override;
        void calcppVectorpEJpEJ() override;
        FMatDsptr getpVectorpXJ() override;
        FMatDsptr getpVectorpEJ() override;
        FMatFColDsptr getppVectorpEJpEJ() override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FMatDsptr prIeJeKepXJ;
        FMatDsptr prIeJeKepEJ;
        FMatFColDsptr pprIeJeKepEJpEJ;
    };
}

