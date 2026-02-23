/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIeqJeq.h"

namespace MbD {
    class DirectionCosineConstraintIeqtJeq : public DirectionCosineConstraintIeqJeq
    {
    public:
        DirectionCosineConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIeqJeq(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void preAccIC() override;
        void preVelIC() override;
        void fillVelICError(FColDsptr col) override;
        ConstraintType type() override;
        void initaAijIeJe() override;
        double pGpt = std::numeric_limits<double>::min();
        FRowDsptr ppGpEIpt;
        FRowDsptr ppGpEJpt;
        double ppGptpt = std::numeric_limits<double>::min();

    };
}

