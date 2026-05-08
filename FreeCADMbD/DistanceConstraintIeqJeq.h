/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistanceConstraintIeqJe.h"

namespace MbD {
    class DistanceConstraintIeqJeq : public DistanceConstraintIeqJe
    {
        //pGpXJ pGpEJ ppGpXIpXJ ppGpEIpXJ ppGpXJpXJ ppGpXIpEJ ppGpEIpEJ ppGpXJpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        DistanceConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIeqJe(frmi, frmj) {}
        static std::shared_ptr<DistanceConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;

        FRowDsptr pGpXJ, pGpEJ;
        FMatDsptr ppGpXIpXJ, ppGpEIpXJ, ppGpXJpXJ, ppGpXIpEJ, ppGpEIpEJ, ppGpXJpEJ, ppGpEJpEJ;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
    };
}

