/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIeJe.h"
#include "DirectionCosineIecJec.h"

namespace MbD {
    class DirectionCosineConstraintIeqJe : public DirectionCosineConstraintIeJe
    {
    public:
        DirectionCosineConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIeJe(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void initializeLocally() override;
        void initializeGlobally() override;
        void calcpGpEI() override;
        void calcppGpEIpEI() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        virtual void initaAijIeJe();

    };
}

