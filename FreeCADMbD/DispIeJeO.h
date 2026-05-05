/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicVectorIeJe.h"

namespace MbD {
    class DispIeJeO : public KinematicVectorIeJe
    {
        //rIeJeO = rOJeO - rOIeO
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * rJpJeJp) - (rOIpO(qXI) + aAOIp(qEI) * rIpIeIp)
        //rIeJeO = (rOJpO(qXJ) + aAOJp(qEJ) * (rJpJmJp + aAJpJm * rJmJeJm(t))) 
        //         - (rOIpO(qXI) + aAOIp(qEI) * (rIpImIp + aAIpIm * rImIeIm(t)))
    public:
        DispIeJeO() {}
        DispIeJeO(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicVectorIeJe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcVector() override;
        FColDsptr getVector() override;
        FMatDsptr getpVectorpXI() override;
        FMatDsptr getpVectorpEI() override;
        FMatDsptr getpVectorpXJ() override;
        FMatDsptr getpVectorpEJ() override;
        FMatDsptr getppCompipEIpEI(size_t axis) override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FColDsptr getpVectorpt() override;
        FMatDsptr getppVectorpEIpt() override;
        FColDsptr getppVectorptpt() override;
        bool hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const override;

        FColDsptr rIeJeO;
    };
}

