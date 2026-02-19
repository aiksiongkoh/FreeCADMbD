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
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeJeqO() {}
        DispIeJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeO(frmi, frmj) {}
        static std::shared_ptr<DispIeJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr getprIeJeOpXJ() override;
        FMatDsptr getprIeJeOpEJ() override;

        FMatDsptr prIeJeOpXJ;
        FMatDsptr prIeJeOpEJ;
        FMatFColDsptr pprIeJeOpEJpEJ;
    };
}

