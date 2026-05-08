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
    class VelRadIeJeq : public VelRadIeJe
    {
        //pvIeJepXJ pvIeJepEJ pvIeJepXdotJ pvIeJepEdotJ 
    public:
        VelRadIeJeq() {}
        VelRadIeJeq(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeJe(frmi, frmj) {}
        static std::shared_ptr<VelRadIeJeq> With();
        static std::shared_ptr<VelRadIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEdotJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXdotJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr pvIeJepXJ, pvIeJepEJ, pvIeJepXdotJ, pvIeJepEdotJ;
    };
}

