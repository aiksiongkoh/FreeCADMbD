/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DistIecJec.h"

namespace MbD {
    class DistIecJeqc : public DistIecJec
    {
        //prIeJepXJ prIeJepEJ pprIeJepXJpXJ pprIeJepXJpEJ pprIeJepEJpEJ prIeJeOpEJT 
    public:
        DistIecJeqc() {}
        DistIecJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistIecJec(frmi, frmj) {}
        static std::shared_ptr<DistIecJeqc> With();
        static std::shared_ptr<DistIecJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPrivate() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FMatDsptr ppvaluepXJpXJ() override;
        FMatDsptr puIeJeOpEJ() override;
        FMatDsptr puIeJeOpXJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr prIeJepXJ, prIeJepEJ;
        FMatDsptr pprIeJepXJpXJ, pprIeJepXJpEJ, pprIeJepEJpEJ, prIeJeOpEJT;
    };
}

