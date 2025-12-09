/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispCompIecJecKec.h"

namespace MbD {
    class DispCompIecJecKeqc : public DispCompIecJecKec
    {
        //priIeJeKepEK ppriIeJeKepEKpEK pAjOKepEKT ppAjOKepEKpEK 
    public:
        DispCompIecJecKeqc() {}
        DispCompIecJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : DispCompIecJecKec(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<DispCompIecJecKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        void initializeGlobally() override;
        FMatDsptr ppvaluepEKpEK() override;
        FRowDsptr pvaluepEK() override;

        FRowDsptr priIeJeKepEK;
        FMatDsptr ppriIeJeKepEKpEK;
        FMatDsptr pAjOKepEKT;
        FMatFColDsptr ppAjOKepEKpEK;
    };
}

