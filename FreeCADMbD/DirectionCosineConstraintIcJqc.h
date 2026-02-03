/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DirectionCosineConstraintIJ.h"

namespace MbD {
    class DirectionCosineConstraintIcJqc : public DirectionCosineConstraintIJ
    {
        //pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
    public:
        DirectionCosineConstraintIcJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIJ(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void addToJointTorqueI(FColDsptr col) override;
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void initaAijIeJe() override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        FRowDsptr pGpEI();

        FRowDsptr pGpEJ;
        FMatDsptr ppGpEJpEJ;
        size_t iqEJ = SIZE_MAX;
    };
}

