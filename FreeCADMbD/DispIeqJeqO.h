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
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqJeqO() {}
        DispIeqJeqO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeO(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeqO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr getprIeJeOpXJ() override;
        FMatDsptr getprIeJeOpEJ() override;

        FMatDsptr prIeJeOpXJ;
        FMatDsptr prIeJeOpEJ;
        FMatFColDsptr pprIeJeOpEJpEJ;
    };
}

