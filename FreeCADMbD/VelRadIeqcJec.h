/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIecJec.h"

namespace MbD {
    class VelRadIeqcJec : public VelRadIecJec
    {
        //pvIeJepXI pvIeJepEI pvIeJepXdotI pvIeJepEdotI 
    public:
        VelRadIeqcJec() {}
		VelRadIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIecJec(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqcJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        FRowDsptr pvaluepEdotI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXdotI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr pvIeJepXI, pvIeJepEI, pvIeJepXdotI, pvIeJepEdotI;
    };
}

