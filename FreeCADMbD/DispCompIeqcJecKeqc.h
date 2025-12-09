/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispCompIecJecKeqc.h"

namespace MbD {
    class DispCompIeqcJecKeqc : public DispCompIecJecKeqc
    {
        //priIeJeKepXI priIeJeKepEI ppriIeJeKepXIpEK ppriIeJeKepEIpEI ppriIeJeKepEIpEK 
    public:
        DispCompIeqcJecKeqc() {}
        DispCompIeqcJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : DispCompIecJecKeqc(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<DispCompIeqcJecKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        FRowDsptr pvaluepXI() override;
        FRowDsptr pvaluepEI() override;
        FMatDsptr ppvaluepXIpEK() override;
        FMatDsptr ppvaluepEIpEK() override;
        FMatDsptr ppvaluepEIpEI() override;

        FRowDsptr priIeJeKepXI;
        FRowDsptr priIeJeKepEI;
        FMatDsptr ppriIeJeKepXIpEK;
        FMatDsptr ppriIeJeKepEIpEI;
        FMatDsptr ppriIeJeKepEIpEK;
    };
}

