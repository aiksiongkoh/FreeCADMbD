/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJeqcKec.h"

namespace MbD {
    class DispCompIectJeqcKect : public DispCompIecJeqcKec
    {
        //priIeJeKepXJ priIeJeKepEJ ppriIeJeKepEJpEJ 
    public:
        DispCompIectJeqcKect() {}
        DispCompIectJeqcKect(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : DispCompIecJeqcKec(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<DispCompIectJeqcKect> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void preAccIC() override;
        void preVelIC() override;
        FRowDsptr ppvaluepXJpt() override;
        FRowDsptr ppvaluepEJpt() override;
        double ppvalueptpt() override;
        double pvaluept() override;

        double priIeJeKept = 0.0;
        FRowDsptr ppriIeJeKepXJpt;
        FRowDsptr ppriIeJeKepEJpt;
        double ppriIeJeKeptpt = 0.0;
    };
}

