/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "GearConstraintIqcJc.h"

namespace MbD {
    class GearConstraintIqcJqc : public GearConstraintIqcJc
    {
        //pGpXJ pGpEJ ppGpXIpXJ ppGpXIpEJ ppGpEIpXJ ppGpEIpEJ ppGpXJpXJ ppGpXJpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        GearConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : GearConstraintIqcJc(frmi, frmj) {}
        static std::shared_ptr<GearConstraintIqcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcpGpEJ();
        void calcpGpXJ();
        void calcppGpEIpEJ();
        void calcppGpEIpXJ();
        void calcppGpEJpEJ();
        void calcppGpXIpEJ();
        void calcppGpXIpXJ();
        void calcppGpXJpEJ();
        void calcppGpXJpXJ();
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void initorbitsIJ() override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;

        FRowDsptr pGpXJ, pGpEJ;
        FMatDsptr ppGpXIpXJ, ppGpXIpEJ, ppGpEIpXJ, ppGpEIpEJ, ppGpXJpXJ, ppGpXJpEJ, ppGpEJpEJ;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;

    };
}

