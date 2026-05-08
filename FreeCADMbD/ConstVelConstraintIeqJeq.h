/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstVelConstraintIeqJe.h"

namespace MbD {
    class ConstVelConstraintIeqJeq : public ConstVelConstraintIeqJe
    {
        //pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
    public:
        ConstVelConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : ConstVelConstraintIeqJe(frmi, frmj) {}
        static std::shared_ptr<ConstVelConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void initA01IeJe() override;
        void initA10IeJe() override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        std::string constraintSpec() override;

        FRowDsptr pGpEJ;
        FMatDsptr ppGpEIpEJ;
        FMatDsptr ppGpEJpEJ;
        size_t iqEJ = SIZE_MAX;
    };
}

