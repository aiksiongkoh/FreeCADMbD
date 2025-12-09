/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstVelConstraintIJ.h"

namespace MbD {
    class ConstVelConstraintIqcJc : public ConstVelConstraintIJ
    {
        //pGpEI ppGpEIpEI iqEI 
    public:
        ConstVelConstraintIqcJc(EndFrmsptr frmi, EndFrmsptr frmj) : ConstVelConstraintIJ(frmi, frmj) {}
        static std::shared_ptr<ConstVelConstraintIqcJc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
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

        FRowDsptr pGpEI;
        FMatDsptr ppGpEIpEI;
        size_t iqEI = SIZE_MAX;
    };
}
