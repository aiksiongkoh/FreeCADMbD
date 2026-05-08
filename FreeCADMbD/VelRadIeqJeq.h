/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeqJe.h"

namespace MbD {
    class VelRadIeqJeq : public VelRadIeqJe
    {
        //pvIeJepXJ pvIeJepEJ pvIeJepXdotJ pvIeJepEdotJ 
    public:
        VelRadIeqJeq() {}
        VelRadIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqJe(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqJeq> With();
        static std::shared_ptr<VelRadIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEdotJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXdotJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr pvIeJepXJ, pvIeJepEJ, pvIeJepXdotJ, pvIeJepEdotJ;
    };
}

