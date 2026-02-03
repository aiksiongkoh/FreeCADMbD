/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJecIe.h"

namespace MbD {
    class DispCompIecJeqcIe : public DispCompIecJecIe
    {
        //priIeJeIepXJ priIeJeIepEJ ppriIeJeIepXJpEJ ppriIeJeIepEJpEJ pAjOIepEJT ppAjOIepEJpEJ 
    public:
        DispCompIecJeqcIe() {}
        DispCompIecJeqcIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : DispCompIecJecIe(frmi, frmj, axis) {}
        static std::shared_ptr<DispCompIecJeqcIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void initialize() override;

        void calcppvaluepEJpEJ() override;
        void calcppvaluepXJpEJ() override;
        void calcpvaluepEJ() override;
        void calcpvaluepXJ() override;
        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;

        FRowDsptr priIeJeIepXJ, priIeJeIepEJ;
        FMatDsptr ppriIeJeIepXJpEJ, ppriIeJeIepEJpEJ, pAjOIepEJT;
        FMatFColDsptr ppAjOIepEJpEJ;
    };
}

