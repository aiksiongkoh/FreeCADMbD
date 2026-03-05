/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeqJeqO.h"

namespace MbD {
    class DispIeqtJeqO : public DispIeqJeqO
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIeqtJeqO() {}
        DispIeqtJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeqO(frmi, frmj) {}
        static std::shared_ptr<DispIeqtJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void preVelIC() override;
        void preAccIC() override;
        void calcpvaluept() override;
        void calcppvaluepEIpt();
        void calcppvalueptpt() override;
        FMatDsptr getprIeJeOpXJ() override;
        FMatDsptr getprIeJeOpEJ() override;
        FColDsptr getprIeJeOpt() override;
        FMatDsptr getpprIeJeOpEIpt() override;
        FColDsptr getpprIeJeOptpt() override;

        FColDsptr prIeJeOpt;
        FMatDsptr pprIeJeOpEIpt;
        FColDsptr pprIeJeOptpt;
    };
}

