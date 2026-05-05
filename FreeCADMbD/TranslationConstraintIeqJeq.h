/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "TranslationConstraintIeqJe.h"

namespace MbD {
    class TranslationConstraintIeqJeq : public TranslationConstraintIeqJe
    {
        //pGpXJ pGpEJ ppGpEIpXJ ppGpEIpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        TranslationConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIeqJe(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void simUpdateAll() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpEIpXJ() override;
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
        size_t iqXJ = SIZE_MAX;
        size_t iqEJ = SIZE_MAX;
        FRowDsptr pGpXJ;
        FRowDsptr pGpEJ;
        FMatDsptr ppGpEIpXJ;
        FMatDsptr ppGpEIpEJ;
        FMatDsptr ppGpEJpEJ;

    };
}

