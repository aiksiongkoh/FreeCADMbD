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
    class VelRadIecJeqc : public VelRadIecJec
    {
        //pvIeJepXJ pvIeJepEJ pvIeJepXdotJ pvIeJepEdotJ 
    public:
        VelRadIecJeqc() {}
        VelRadIecJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIecJec(frmi, frmj) {}
        static std::shared_ptr<VelRadIecJeqc> With();
        static std::shared_ptr<VelRadIecJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEdotJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXdotJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr pvIeJepXJ, pvIeJepEJ, pvIeJepXdotJ, pvIeJepEdotJ;
    };
}

