/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispCompIeqcJeqcKeqc.h"

namespace MbD {
    class DispCompIeqcJeqcKeqct : public DispCompIeqcJeqcKeqc
    {
        //priIeJeKept ppriIeJeKepXIpt ppriIeJeKepEIpt ppriIeJeKepXJpt ppriIeJeKepEJpt ppriIeJeKepEKpt ppriIeJeKeptpt 
    public:
        DispCompIeqcJeqcKeqct() {}
        DispCompIeqcJeqcKeqct(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : DispCompIeqcJeqcKeqc(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<DispCompIeqcJeqcKeqct> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        void initializeGlobally() override;
        FRowDsptr ppvaluepXIpt() override;
        FRowDsptr ppvaluepEIpt() override;
        FRowDsptr ppvaluepEKpt() override;
        FRowDsptr ppvaluepXJpt() override;
        FRowDsptr ppvaluepEJpt() override;
        double ppvalueptpt() override;
        double pvaluept() override;
        void preAccIC() override;
        void preVelIC() override;

        double priIeJeKept = 0.0;
        FRowDsptr ppriIeJeKepXIpt;
        FRowDsptr ppriIeJeKepEIpt;
        FRowDsptr ppriIeJeKepXJpt;
        FRowDsptr ppriIeJeKepEJpt;
        FRowDsptr ppriIeJeKepEKpt;
        double ppriIeJeKeptpt = 0.0;
    };
}

