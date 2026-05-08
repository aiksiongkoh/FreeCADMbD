/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AngleZIeJe.h"

namespace MbD {
    class AngleZIeqJe : public AngleZIeJe
    {
        //pthezpEI ppthezpEIpEI pcthezpEI psthezpEI 
    public:
        AngleZIeqJe() {}
        AngleZIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIeJe(frmi, frmj) {}
        static std::shared_ptr<AngleZIeqJe> With();
        static std::shared_ptr<AngleZIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void init_aAijIeJe() override;
        FMatDsptr ppvaluepEIpEI() override;
        FRowDsptr pvaluepEI() override;

        FRowDsptr pthezpEI, pcthezpEI, psthezpEI;
        FMatDsptr ppthezpEIpEI;
    };
}

