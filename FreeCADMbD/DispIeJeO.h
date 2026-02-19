/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIeJe.h"

namespace MbD {
    class DispIeJeO : public KinematicIeJe
    {
    public:
        DispIeJeO() {}
        DispIeJeO(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIeJe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        virtual FMatDsptr getprIeJeOpXI();
        virtual FMatDsptr getprIeJeOpEI();
        virtual FMatDsptr getprIeJeOpXJ();
        virtual FMatDsptr getprIeJeOpEJ();
        virtual FMatDsptr getppriIeJeOpEIpEI(size_t axis);
        virtual FMatDsptr getppriIeJeOpEJpEJ(size_t axis);
        virtual FColDsptr getprIeJeOpt();
        virtual FColDsptr getpprIeJeOptpt();
        bool hasSameEndFrms(const std::shared_ptr<DispIeJeO> other) const;

        FColDsptr rIeJeO;
    };
}

