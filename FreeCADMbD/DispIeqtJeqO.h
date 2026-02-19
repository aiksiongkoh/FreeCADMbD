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
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqtJeqO() {}
        DispIeqtJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeqO(frmi, frmj) {}
        static std::shared_ptr<DispIeqtJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void initializeGlobally() override;
        void preVelIC() override;
        void preAccIC() override;
        FMatDsptr getprIeJeOpXJ() override;
        FMatDsptr getprIeJeOpEJ() override;
        FColDsptr getprIeJeOpt() override;
        FColDsptr getpprIeJeOptpt() override;

        FColDsptr prIeJeOpt;
        FColDsptr pprIeJeOptpt;
    };
}

