/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispIeqJeqKe.h"

namespace MbD {
    class DispIeqJeqKeq : public DispIeqJeqKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqJeqKeq() {}
        DispIeqJeqKeq(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeqKe(frmi, frmj) {}
        static std::shared_ptr<DispIeqJeqKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcpvaluepEK() override;
        void calcppvaluepXIpEK() override;
        void calcppvaluepEIpEK() override;
        void calcppvaluepXJpEK() override;
        void calcppvaluepEJpEK() override;
        void calcppvaluepEKpEK() override;
        void initializeGlobally() override;
        FMatDsptr prIeJeKepEK;
        FMatFColDsptr pprIeJeKepXIpEK;
        FMatFColDsptr pprIeJeKepEIpEK;
        FMatFColDsptr pprIeJeKepXJpEK;
        FMatFColDsptr pprIeJeKepEJpEK;
        FMatFColDsptr pprIeJeKepEKpEK;

    };
}

