/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "RackPinConstraintIeqJe.h"

namespace MbD {
    class RackPinConstraintIeqJeq : public RackPinConstraintIeqJe
    {
        //pGpXJ pGpEJ ppGpEIpXJ ppGpEIpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        RackPinConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : RackPinConstraintIeqJe(frmi, frmj) {}
        static std::shared_ptr<RackPinConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void initxIeJeIe() override;
        void initthezIeJe() override;
        void calcpGpEJ();
        void calcpGpXJ();
        void calcppGpEIpEJ();
        void calcppGpEIpXJ();
        void calcppGpEJpEJ();
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
        FMatDsptr ppGpEIpXJ, ppGpEIpEJ, ppGpEJpEJ;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
    };
}

