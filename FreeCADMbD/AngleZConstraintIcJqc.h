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
    class AngleZConstraintIcJqc : public AngleZConstraintIJ
    {
        //pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
    public:
        AngleZConstraintIcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZConstraintIJ(frmi, frmj) {}

        void initthezIeJe() override;
        void calcpGpEJ();
        void calcppGpEJpEJ();
        void addToJointTorqueI(FColDsptr col) override;
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;

        FRowDsptr pGpEJ;
        FMatDsptr ppGpEJpEJ;
        size_t iqEJ = SIZE_MAX;
    };
}

