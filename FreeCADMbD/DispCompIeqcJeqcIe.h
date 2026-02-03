/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DispCompIeqcJecIe.h"

namespace MbD {
    class DispCompIeqcJeqcIe : public DispCompIeqcJecIe
    {
        //priIeJeIepXJ priIeJeIepEJ ppriIeJeIepEIpXJ ppriIeJeIepEIpEJ ppriIeJeIepEJpEJ 
    public:
        DispCompIeqcJeqcIe() {}
        DispCompIeqcJeqcIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : DispCompIeqcJecIe(frmi, frmj, axis) {}
        static std::shared_ptr<DispCompIeqcJeqcIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void initialize() override;

        void calcppvaluepEIpEJ() override;
        void calcppvaluepEIpXJ() override;
        void calcppvaluepEJpEJ() override;
        void calcpvaluepEJ() override;
        void calcpvaluepXJ() override;
        void simUpdateAll() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr priIeJeIepXJ, priIeJeIepEJ;
        FMatDsptr ppriIeJeIepEIpXJ, ppriIeJeIepEIpEJ, ppriIeJeIepEJpEJ;
    };
}

