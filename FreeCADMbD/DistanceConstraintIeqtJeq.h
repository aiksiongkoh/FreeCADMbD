/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistanceConstraintIeqJeq.h"

namespace MbD {
    class DistanceConstraintIeqtJeq : public DistanceConstraintIeqJeq
    {
        //pGpt ppGpXIpt ppGpEIpt ppGpXJpt ppGpEJpt ppGptpt 
    public:
        DistanceConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIeqJeq(frmi, frmj) {}
        static std::shared_ptr<DistanceConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        
        void fillVelICError(FColDsptr col) override;
        ConstraintType type() override;

        double pGpt = 0.0, ppGptpt = 0.0;
        FRowDsptr ppGpXIpt, ppGpEIpt, ppGpXJpt, ppGpEJpt;
            
    };
}

