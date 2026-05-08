/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DistIeJe.h"

namespace MbD {
    class DistIeJeq : public DistIeJe
    {
    public:
        DistIeJeq() {}
        DistIeJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeJe(frmi, frmj) {}
        static std::shared_ptr<DistIeJeq> With();
        static std::shared_ptr<DistIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
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

