/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistancexyConstraintIeqJe.h"

namespace MbD {
    class DistancexyConstraintIeqJeq : public DistancexyConstraintIeqJe
    {
        //pGpXJ pGpEJ ppGpXIpXJ ppGpEIpXJ ppGpXJpXJ ppGpXIpEJ ppGpEIpEJ ppGpXJpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        DistancexyConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistancexyConstraintIeqJe(frmi, frmj) {}
        static std::shared_ptr<DistancexyConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcpGpXJ();
        void calcpGpEJ();
        void calcppGpXIpXJ();
        void calcppGpEIpXJ();
        void calcppGpXJpXJ();
        void calcppGpXIpEJ();
        void calcppGpEIpEJ();
        void calcppGpXJpEJ();
        void calcppGpEJpEJ();
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void init_xyIeJeIe() override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;

        FRowDsptr pGpXJ, pGpEJ;
        FMatDsptr ppGpXIpXJ, ppGpEIpXJ, ppGpXJpXJ, ppGpXIpEJ, ppGpEIpEJ, ppGpXJpEJ, ppGpEJpEJ;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
    };
}

