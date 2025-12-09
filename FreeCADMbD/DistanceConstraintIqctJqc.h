/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistanceConstraintIqcJqc.h"

namespace MbD {
    class DistanceConstraintIqctJqc : public DistanceConstraintIqcJqc
    {
        //pGpt ppGpXIpt ppGpEIpt ppGpXJpt ppGpEJpt ppGptpt 
    public:
		DistanceConstraintIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIqcJqc(frmi, frmj) {}
        static std::shared_ptr<DistanceConstraintIqctJqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        
        void fillVelICError(FColDsptr col) override;
        ConstraintType type() override;

        double pGpt = 0.0, ppGptpt = 0.0;
        FRowDsptr ppGpXIpt, ppGpEIpt, ppGpXJpt, ppGpEJpt;
            
    };
}

