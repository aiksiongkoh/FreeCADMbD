/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistanceConstraintIJ.h"

namespace MbD {
    class DistanceConstraintIeqJe : public DistanceConstraintIJ
    {
        //pGpXI pGpEI ppGpXIpXI ppGpXIpEI ppGpEIpEI iqXI iqEI 
    public:
        DistanceConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIJ(frmi, frmj) {}
        static std::shared_ptr<DistanceConstraintIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        std::string constraintSpec() override;

        FRowDsptr pGpXI, pGpEI;
        FMatDsptr ppGpXIpXI, ppGpXIpEI, ppGpEIpEI;
        size_t iqXI = SIZE_MAX, iqEI = SIZE_MAX;
    };
}

