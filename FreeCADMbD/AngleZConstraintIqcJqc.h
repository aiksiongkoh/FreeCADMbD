/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <cstdint>

#include "AngleZConstraintIqcJc.h"

namespace MbD {
    class AngleZConstraintIqcJqc : public AngleZConstraintIqcJc
    {
        //pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
    public:
		AngleZConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZConstraintIqcJc(frmi, frmj) {}

        void initthezIeJe() override;
        void calc_pGpEJ();
        void calc_ppGpEIpEJ();
        void calc_ppGpEJpEJ();
        void calcPostDynCorrectorIteration() override;
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

