/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineIeqJeq.h"

namespace MbD {
    class DirectionCosineIeqtJeq : public DirectionCosineIeqJeq
    {
        //pAijIeJept ppAijIeJepEIpt ppAijIeJepEJpt ppAijIeJeptpt 
    public:
        DirectionCosineIeqtJeq();
        DirectionCosineIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineIeqJeq(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;

        void simUpdateAll() override;
        void initializeGlobally() override;
        FRowDsptr ppvaluepEIpt() override;
        FRowDsptr ppvaluepEJpt() override;
        double ppvalueptpt() override;
        void preAccIC() override;
        void preVelIC() override;
        double pvaluept() override;

        double pAijIeJept;
        FRowDsptr ppAijIeJepEIpt;
        FRowDsptr ppAijIeJepEJpt;
        double ppAijIeJeptpt;
    };
}

