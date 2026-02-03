/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJecO.h"

namespace MbD {
    class DispCompIecJeqcO : public DispCompIecJecO
    {
        //priIeJeOpXJ priIeJeOpEJ ppriIeJeOpEJpEJ 
    public:
        DispCompIecJeqcO() {}
        DispCompIecJeqcO(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : DispCompIecJecO(frmi, frmj, axisO) {}
        static std::shared_ptr<DispCompIecJeqcO> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr priIeJeOpXJ;
        FRowDsptr priIeJeOpEJ;
        FMatDsptr ppriIeJeOpEJpEJ;
    };
}

