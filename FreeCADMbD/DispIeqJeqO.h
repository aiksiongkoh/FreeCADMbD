/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeO.h"

namespace MbD {
    class DispIeqJeqO : public DispIeqJeO
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIeqJeqO() {}
        DispIeqJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeO(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpVectorpXJ() override;
        void calcpVectorpEJ() override;
        void calcppVectorpEJpEJ() override;
        void initializeGlobally() override;
        FMatDsptr getpVectorpXJ() override;
        FMatDsptr getpVectorpEJ() override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FMatDsptr prIeJeOpXJ;
        FMatDsptr prIeJeOpEJ;
        FMatFColDsptr pprIeJeOpEJpEJ;
    };
}

