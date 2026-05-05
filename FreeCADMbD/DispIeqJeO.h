/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeJeO.h"

namespace MbD {
    class DispIeqJeO : public DispIeJeO
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIeqJeO() {}
        DispIeqJeO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeO(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXI() override;
        void calcpVectorpEI() override;
        void calcppVectorpEIpEI() override;
        void initializeGlobally() override;
        FMatDsptr getpVectorpXI() override;
        FMatDsptr getpVectorpEI() override;
        FMatFColDsptr getppVectorpEIpEI() override;
        FMatDsptr getppCompipEIpEI(size_t axis) override;

        FMatDsptr prIeJeOpXI;
        FMatDsptr prIeJeOpEI;
        FMatFColDsptr pprIeJeOpEIpEI;
    };
}

