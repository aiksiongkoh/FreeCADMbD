/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeKe.h"

namespace MbD {
    class DispIeqJeKeq : public DispIeqJeKe
    {
        //prIeJeOpXI prIeJeOpEI pprIeJeOpEIpEI 
    public:
        DispIeqJeKeq() {}
        DispIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeKe(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpvaluepEK() override;
        void calcppvaluepEKpEK() override;
        void calcppvaluepXIpEK() override;
        void calcppvaluepEIpEK() override;
        void initializeGlobally() override;
        FMatDsptr prIeJeKepEK;
        FMatFColDsptr pprIeJeKepXIpEK;
        FMatFColDsptr pprIeJeKepEIpEK;
        FMatFColDsptr pprIeJeKepEKpEK;

    };
}

