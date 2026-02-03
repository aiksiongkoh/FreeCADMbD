/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"
#include "DirectionCosineIecJec.h"

namespace MbD {
    class DirectionCosineConstraintIeqJeq : public ConstraintIeJe
    {
    public:
        DirectionCosineConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : axisI(axisi), axisJ(axisj), ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<DirectionCosineConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void simUpdateAll() override;
        void calcG() override;
        void calcpGpXI() override;
        void calcpGpEI() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpXIpXI() override;
        void calcppGpXIpEI() override;
        void calcppGpXIpXJ() override;
        void calcppGpXIpEJ() override;
        void calcppGpEIpEI() override;
        void calcppGpEIpXJ() override;
        void calcppGpEIpEJ() override;
        void calcppGpXJpXJ() override;
        void calcppGpXJpEJ() override;
        void calcppGpEJpEJ() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        virtual void initaAijIeJe();
        std::string constraintSpec() override;

        size_t axisI = SIZE_MAX, axisJ = SIZE_MAX;
        std::shared_ptr<DirectionCosineIecJec> aAijIeJe;

    };
}

