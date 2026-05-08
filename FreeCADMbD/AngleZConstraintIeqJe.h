/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <cstdint>

#include "AngleZConstraintIJ.h"

namespace MbD {
    class AngleZConstraintIeqJe : public AngleZConstraintIJ
    {
        //pGpEI ppGpEIpEI iqEI 
    public:
        AngleZConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZConstraintIJ(frmi, frmj) {}

        void initthezIeJe() override;
        void addToJointTorqueI(FColDsptr col) override;
        void calcpGpEI();
        void calcppGpEIpEI();
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;

        FRowDsptr pGpEI;
        FMatDsptr ppGpEIpEI;
        size_t iqEI = SIZE_MAX;

    };
}
