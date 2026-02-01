/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "TranslationConstraintIJ.h"

namespace MbD {
    class TranslationConstraintIcJqc : public TranslationConstraintIJ
    {
        //pGpXJ pGpEJ ppGpEIpXJ ppGpEIpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        TranslationConstraintIcJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIJ(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void calcPostDynCorrectorIteration() override;
        void initriIeJeIe() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;

        FRowDsptr pGpXJ, pGpEJ;
        FMatDsptr ppGpEIpXJ, ppGpEIpEJ, ppGpEJpEJ;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
    };
}

