/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIeJeq.h"

namespace MbD {
    class DirectionCosineConstraintIetJeq : public DirectionCosineConstraintIeJeq
    {
    public:
        DirectionCosineConstraintIetJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIeJeq(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIetJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void preAccIC() override;
        void preVelIC() override;
        void fillVelICError(FColDsptr col) override;
        ConstraintType type() override;
        void initaAijIeJe() override;
        void fillAccICIterError(FColDsptr col);
        double pGpt = std::numeric_limits<double>::min();
        FRowDsptr ppGpEJpt;
        double ppGptpt = std::numeric_limits<double>::min();

    };
}

