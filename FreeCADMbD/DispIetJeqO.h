/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIecJeqcO.h"

namespace MbD {
    class DispIetJeqO : public DispIecJeqcO
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIetJeqO() {}
        DispIetJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIecJeqcO(frmi, frmj) {}
        static std::shared_ptr<DispIetJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
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

