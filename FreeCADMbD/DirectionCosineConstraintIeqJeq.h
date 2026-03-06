/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIeqJe.h"
#include "DirectionCosineIecJec.h"

namespace MbD {
    class DirectionCosineConstraintIeqJeq : public DirectionCosineConstraintIeqJe
    {
    public:
        DirectionCosineConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIeqJe(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void simUpdateAll() override;
        void calcpGpEJ() override;
        void calcppGpEIpEJ() override;
        void calcppGpEJpEJ() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void initaAijIeJe() override;
        size_t iqEJ = SIZE_MAX;
        FRowDsptr pGpEJ;
        FMatDsptr ppGpEIpEJ;
        FMatDsptr ppGpEJpEJ;

    };
}

