/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DirectionCosineIeJeq.h"

namespace MbD
{
    class DirectionCosineIetJeq : public DirectionCosineIeJeq
    {
        // pAijIeJept ppAijIeJepEIpt ppAijIeJepEJpt ppAijIeJeptpt
    public:
        DirectionCosineIetJeq() {}
        DirectionCosineIetJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineIeJeq(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineIetJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;
        void initializeGlobally() override;
        void simUpdateAll() override;

        FRowDsptr ppvaluepEJpt() override;
        double ppvalueptpt() override;
        void preAccIC() override;
        void preVelIC() override;
        double pvaluept() override;

        double pAijIeJept;
        FRowDsptr ppAijIeJepEJpt;
        double ppAijIeJeptpt = 0.0;
    };
}
