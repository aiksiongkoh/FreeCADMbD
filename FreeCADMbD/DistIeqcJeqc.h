/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistIeqcJec.h"

namespace MbD {
    class DistIeqcJeqc : public DistIeqcJec
    {
        //prIeJepXJ prIeJepEJ pprIeJepXIpXJ pprIeJepEIpXJ pprIeJepXJpXJ pprIeJepXIpEJ pprIeJepEIpEJ pprIeJepXJpEJ pprIeJepEJpEJ prIeJeOpEJT 
    public:
        DistIeqcJeqc() {}
        DistIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeqcJec(frmi, frmj) {}
        static std::shared_ptr<DistIeqcJeqc> With();
        static std::shared_ptr<DistIeqcJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPrivate() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FMatDsptr ppvaluepXIpEJ() override;
        FMatDsptr ppvaluepXIpXJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FMatDsptr ppvaluepXJpXJ() override;
        FMatDsptr puIeJeOpEJ() override;
        FMatDsptr puIeJeOpXJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr prIeJepXJ, prIeJepEJ;
        FMatDsptr pprIeJepXIpXJ, pprIeJepEIpXJ, pprIeJepXJpXJ, pprIeJepXIpEJ, pprIeJepEIpEJ, pprIeJepXJpEJ, pprIeJepEJpEJ, prIeJeOpEJT;
    };
}

