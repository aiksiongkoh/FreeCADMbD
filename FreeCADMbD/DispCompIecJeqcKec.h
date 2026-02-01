/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJecKec.h"

namespace MbD {
    class DispCompIecJeqcKec : public DispCompIecJecKec
    {
        //priIeJeKepXJ priIeJeKepEJ ppriIeJeKepEJpEJ 
    public:
        DispCompIecJeqcKec() {}
        DispCompIecJeqcKec(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : DispCompIecJecKec(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<DispCompIecJeqcKec> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        FRowDsptr pvaluepXJ() override;
        FRowDsptr pvaluepEJ() override;
        FMatDsptr ppvaluepEJpEJ() override;

        FRowDsptr priIeJeKepXJ;
        FRowDsptr priIeJeKepEJ;
        FMatDsptr ppriIeJeKepEJpEJ;
    };
}

