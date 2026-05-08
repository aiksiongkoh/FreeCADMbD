/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DistIeqJeq.h"

namespace MbD {
    class DistIeqtJeq : public DistIeqJeq
    {
    public:
        DistIeqtJeq() {}
        DistIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeqJeq(frmi, frmj) {}
        static std::shared_ptr<DistIeqtJeq> With();
        static std::shared_ptr<DistIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        double prIeJept = 0.0;
        FRowDsptr pprIeJepXIpt;
        FRowDsptr pprIeJepEIpt;
        FRowDsptr pprIeJepXJpt;
        FRowDsptr pprIeJepEJpt;
        double pprIeJeptpt = 0.0;
    };
}

