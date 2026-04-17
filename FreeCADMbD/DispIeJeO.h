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
        virtual FMatDsptr getpVectorpXI();
        virtual FMatDsptr getpVectorpEI();
        virtual FMatDsptr getpVectorpXJ();
        virtual FMatDsptr getpVectorpEJ();
        virtual FMatDsptr getppCompipEIpEI(size_t axis);
        virtual FMatDsptr getppCompipEJpEJ(size_t axis);
        virtual FColDsptr getpVectorpt();
        virtual FMatDsptr getppVectorpEIpt();
        virtual FColDsptr getppVectorptpt();
        virtual bool hasSameEndFrms(const std::shared_ptr<DispIeJeO> other) const;

        FColDsptr rIeJeO;
    };
}

