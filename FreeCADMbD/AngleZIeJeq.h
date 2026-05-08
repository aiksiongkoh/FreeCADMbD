/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AngleZIeJe.h"
#include "EndFrame.h"

namespace MbD {
    class AngleZIeJeq : public AngleZIeJe
    {
        //pthezpEJ ppthezpEJpEJ 
    public:
        AngleZIeJeq() {}
        AngleZIeJeq(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIeJe(frmi, frmj) {}
        static std::shared_ptr<AngleZIeJeq> With();
        static std::shared_ptr<AngleZIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void init_aAijIeJe() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;

        FRowDsptr pthezpEJ;
        FMatDsptr ppthezpEJpEJ;
    };
}

