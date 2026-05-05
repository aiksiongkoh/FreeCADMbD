/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeJeqO.h"

namespace MbD {
    class DispIetJeqO : public DispIeJeqO
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIetJeqO() {}
        DispIetJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeqO(frmi, frmj) {}
        static std::shared_ptr<DispIetJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void preVelIC() override;
        void preAccIC() override;
        void calcpVectorpt() override;
        void calcppVectorptpt() override;
        FColDsptr getpVectorpt() override;
        FColDsptr getppVectorptpt() override;

        FColDsptr prIeJeOpt;
        FColDsptr pprIeJeOptpt;
    };
}

