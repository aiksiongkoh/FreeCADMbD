/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AngleZIeqcJec.h"
#include "EndFramec.h"

namespace MbD {
    class AngleZIeqcJeqc : public AngleZIeqcJec
    {
        //pthezpEJ ppthezpEIpEJ ppthezpEJpEJ 
    public:
		AngleZIeqcJeqc() {}
		AngleZIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIeqcJec(frmi, frmj) {}
        static std::shared_ptr<AngleZIeqcJeqc> With();
        static std::shared_ptr<AngleZIeqcJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        void init_aAijIeJe() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;

        FRowDsptr pthezpEJ;
        FMatDsptr ppthezpEIpEJ, ppthezpEJpEJ;
    };
}

