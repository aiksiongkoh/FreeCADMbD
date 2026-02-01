/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJeqcIe.h"

namespace MbD {
    class DispCompIectJeqcIe : public DispCompIecJeqcIe
    {
        //priIeJeIept ppriIeJeIepXIpt ppriIeJeIepEIpt ppriIeJeIepXJpt ppriIeJeIepEJpt ppriIeJeIeptpt 
    public:
        DispCompIectJeqcIe() {}
        DispCompIectJeqcIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : DispCompIecJeqcIe(frmi, frmj, axis) {}
        static std::shared_ptr<DispCompIectJeqcIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void initialize() override;

        void calc_ppvaluepEJpt() override;
        void calc_ppvalueptpt() override;
        void calc_ppvaluepXJpt() override;
        void calc_pvaluept() override;
        void initializeGlobally() override;
        void preAccIC() override;
        void preVelIC() override;
        FRowDsptr ppvaluepEJpt() override;
        double ppvalueptpt() override;
        FRowDsptr ppvaluepXJpt() override;
        double pvaluept() override;

        double priIeJeIept, ppriIeJeIeptpt;
        FRowDsptr ppriIeJeIepXJpt, ppriIeJeIepEJpt;
    };
}

