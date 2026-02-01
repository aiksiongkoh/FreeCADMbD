/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIecJecO.h"

namespace MbD {
    class DispIeqcJecO : public DispIecJecO
    {
        //prIeJeOpXI prIeJeOpEI pprIeJeOpEIpEI 
    public:
        DispIeqcJecO() {}
        DispIeqcJecO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIecJecO(frmi, frmj) {}
        static std::shared_ptr<DispIeqcJecO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcPostDynCorrectorIteration() override;
        void initializeGlobally() override;
        FMatDsptr getprIeJeOpXI() override;
        FMatDsptr getprIeJeOpEI() override;

        FMatDsptr prIeJeOpXI;
        FMatDsptr prIeJeOpEI;
        FMatFColDsptr pprIeJeOpEIpEI;
    };
}

