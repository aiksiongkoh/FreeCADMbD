/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DistIeqJe.h"

namespace MbD {
    class DistIeqJeq : public DistIeqJe
    {
    public:
        DistIeqJeq() {}
        DistIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeqJe(frmi, frmj) {}
        static std::shared_ptr<DistIeqJeq> With();
        static std::shared_ptr<DistIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
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

