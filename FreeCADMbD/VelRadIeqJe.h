/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeJe.h"

namespace MbD {
    class VelRadIeqJe : public VelRadIeJe
    {
        //pvIeJepXI pvIeJepEI pvIeJepXdotI pvIeJepEdotI 
    public:
        VelRadIeqJe() {}
        VelRadIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeJe(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEdotI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXdotI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr pvIeJepXI, pvIeJepEI, pvIeJepXdotI, pvIeJepEdotI;
    };
}

