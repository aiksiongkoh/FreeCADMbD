/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeKe.h"

namespace MbD {
    class DispIeqJeqKe : public DispIeqJeKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqJeqKe() {}
        DispIeqJeqKe(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeKe(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpvaluepXJ() override;
        void calcpvaluepEJ() override;
        void calcppvaluepEIpXJ() override;
        void calcppvaluepEIpEJ() override;
        void calcppvaluepEJpEJ() override;
        void initializeGlobally() override;
        FMatDsptr prIeJeKepXJ;
        FMatDsptr prIeJeKepEJ;
        FMatFColDsptr pprIeJeKepEJpEJ;

    };
}

