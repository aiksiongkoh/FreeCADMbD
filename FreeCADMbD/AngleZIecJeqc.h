/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AngleZIecJec.h"
#include "EndFramec.h"

namespace MbD {
    class AngleZIecJeqc : public AngleZIecJec
    {
        //pthezpEJ ppthezpEJpEJ 
    public:
        AngleZIecJeqc() {}
        AngleZIecJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIecJec(frmi, frmj) {}
        static std::shared_ptr<AngleZIecJeqc> With();
        static std::shared_ptr<AngleZIecJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        void init_aAijIeJe() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;

        FRowDsptr pthezpEJ;
        FMatDsptr ppthezpEJpEJ;
    };
}

