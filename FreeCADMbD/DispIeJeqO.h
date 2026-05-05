/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeJeO.h"

namespace MbD {
    class DispIeJeqO : public DispIeJeO
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIeJeqO() {}
        DispIeJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeO(frmi, frmj) {}
        static std::shared_ptr<DispIeJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXJ() override;
        void calcpVectorpEJ() override;
        void calcppVectorpEJpEJ() override;
        void initializeGlobally() override;
        FMatDsptr getpVectorpXJ() override;
        FMatDsptr getpVectorpEJ() override;
        FMatFColDsptr getppVectorpEJpEJ() override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FMatDsptr prIeJeOpXJ;
        FMatDsptr prIeJeOpEJ;
        FMatFColDsptr pprIeJeOpEJpEJ;
    };
}

