/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "RackPinConstraintIJ.h"

namespace MbD {
    class RackPinConstraintIeqJe : public RackPinConstraintIJ
    {
        //pGpXI pGpEI ppGpXIpEI ppGpEIpEI iqXI iqEI 
    public:
        RackPinConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : RackPinConstraintIJ(frmi, frmj) {}
        static std::shared_ptr<RackPinConstraintIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void initthezIeJe() override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void calcpGpEI();
        void calcpGpXI();
        void calcppGpEIpEI();
        void calcppGpXIpEI();
        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;

        FRowDsptr pGpXI, pGpEI;
        FMatDsptr ppGpXIpEI, ppGpEIpEI;
        size_t iqXI = SIZE_MAX, iqEI = SIZE_MAX;

    };
}

