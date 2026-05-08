/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <cstdint>

#include "AngleZConstraintIeqJe.h"

namespace MbD {
    class AngleZConstraintIeqJeq : public AngleZConstraintIeqJe
    {
        //pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
    public:
        AngleZConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZConstraintIeqJe(frmi, frmj) {}

        void initthezIeJe() override;
        void calcpGpEJ();
        void calcppGpEIpEJ();
        void calcppGpEJpEJ();
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;

        FRowDsptr pGpEJ;
        FMatDsptr ppGpEIpEJ, ppGpEJpEJ;
        size_t iqEJ = SIZE_MAX;
    };
}

