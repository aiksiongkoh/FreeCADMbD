/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIJ.h"

namespace MbD {
    class DispIecJecO : public KinematicIJ
    {
    public:
        DispIecJecO() {}
        DispIecJecO(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<DispIecJecO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        virtual FMatDsptr getprIeJeOpXI();
        virtual FMatDsptr getprIeJeOpEI();
        virtual FMatDsptr getprIeJeOpXJ();
        virtual FMatDsptr getprIeJeOpEJ();
        virtual FMatDsptr getppriIeJeOpEIpEI(size_t axis);
        virtual FMatDsptr getppriIeJeOpEJpEJ(size_t axis);
        virtual FColDsptr getprIeJeOpt();
        virtual FColDsptr getpprIeJeOptpt();

        FColDsptr rIeJeO;
    };
}

