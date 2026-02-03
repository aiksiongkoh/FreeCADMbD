/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqcJecO.h"

namespace MbD {
    class DispIeqcJeqcO : public DispIeqcJecO
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqcJeqcO() {}
        DispIeqcJeqcO(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqcJecO(frmi, frmj) {}
        static std::shared_ptr<DispIeqcJeqcO> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr getprIeJeOpXJ() override;
        FMatDsptr getprIeJeOpEJ() override;

        FMatDsptr prIeJeOpXJ;
        FMatDsptr prIeJeOpEJ;
        FMatFColDsptr pprIeJeOpEJpEJ;
    };
}

