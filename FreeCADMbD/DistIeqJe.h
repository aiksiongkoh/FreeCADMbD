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
    class DistIeqJe : public DistIeJe
    {
    public:
        DistIeqJe() {}
        DistIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeJe(frmi, frmj) {}
        static std::shared_ptr<DistIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPrivate() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepXIpXI() override;
        FMatDsptr puIeJeOpEI() override;
        FMatDsptr puIeJeOpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr prIeJepXI, prIeJepEI;
        FMatDsptr pprIeJepXIpXI, pprIeJepXIpEI, pprIeJepEIpEI, mprIeJeOpEIT;
    };
}

