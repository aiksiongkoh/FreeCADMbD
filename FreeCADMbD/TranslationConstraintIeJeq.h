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
    class TranslationConstraintIeJeq : public TranslationConstraintIeJe
    {
        //pGpXJ pGpEJ ppGpEIpXJ ppGpEIpEJ ppGpEJpEJ iqXJ iqEJ 
    public:
        TranslationConstraintIeJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIeJe(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void initriIeJeIe() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpEJpEJ() override;
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

    };
}

