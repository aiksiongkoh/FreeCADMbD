/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DirectionCosineConstraintIcJqc.h"

namespace MbD {
    class DirectionCosineConstraintIctJqc : public DirectionCosineConstraintIcJqc
    {
        //pGpt ppGpEIpt ppGpEJpt ppGptpt 
    public:
        DirectionCosineConstraintIctJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIcJqc(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIctJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void initaAijIeJe() override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = 0.0;
        FRowDsptr ppGpEJpt;
        double ppGptpt = 0.0;
    };
}
