/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeqcJec.h"

namespace MbD {
    class VelRadIeqcJeqc : public VelRadIeqcJec
    {
        //pvIeJepXJ pvIeJepEJ pvIeJepXdotJ pvIeJepEdotJ 
    public:
        VelRadIeqcJeqc() {}
		VelRadIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqcJec(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqcJeqc> With();
        static std::shared_ptr<VelRadIeqcJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        FRowDsptr pvaluepEdotJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXdotJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr pvIeJepXJ, pvIeJepEJ, pvIeJepXdotJ, pvIeJepEdotJ;
    };
}

