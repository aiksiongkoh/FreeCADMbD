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
    class DirectionCosineConstraintIeJe : public ConstraintIeJe
    {
    public:
        DirectionCosineConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : axisI(axisi), axisJ(axisj), ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<DirectionCosineConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

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
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        ConstraintType type() override;
        std::string constraintSpec() override;

        void initialize() override;

        size_t axisI = SIZE_MAX, axisJ = SIZE_MAX;
        std::shared_ptr<DirectionCosineIecJec> aAijIeJe;

    };
}

