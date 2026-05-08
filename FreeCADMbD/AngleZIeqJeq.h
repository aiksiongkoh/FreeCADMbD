/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AngleZIeqJe.h"
#include "EndFrame.h"

namespace MbD {
    class AngleZIeqJeq : public AngleZIeqJe
    {
        //pthezpEJ ppthezpEIpEJ ppthezpEJpEJ 
    public:
        AngleZIeqJeq() {}
        AngleZIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIeqJe(frmi, frmj) {}
        static std::shared_ptr<AngleZIeqJeq> With();
        static std::shared_ptr<AngleZIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void init_aAijIeJe() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;

        FRowDsptr pthezpEJ;
        FMatDsptr ppthezpEIpEJ, ppthezpEJpEJ;
    };
}

