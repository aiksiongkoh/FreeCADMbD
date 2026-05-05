/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "TranslationConstraintIeJe.h"

namespace MbD {
    class TranslationConstraintIeqJe : public TranslationConstraintIeJe
    {
        //pGpXI pGpEI ppGpXIpEI ppGpEIpEI iqXI iqEI 
    public:
        TranslationConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIeJe(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void simUpdateAll() override;
        void calcpGpXI() override;
        void calcpGpEI() override;
        void calcppGpXIpEI() override;
        void calcppGpEIpEI() override;
        void fillAccICIterError(FColDsptr col) override;
        void addToJointForceI(FColDsptr col);
        void addToJointTorqueI(FColDsptr col);
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        size_t iqXI = SIZE_MAX;
        size_t iqEI = SIZE_MAX;
        FRowDsptr pGpXI;
        FRowDsptr pGpEI;
        FMatDsptr ppGpXIpEI;
        FMatDsptr ppGpEIpEI;

    };
}

