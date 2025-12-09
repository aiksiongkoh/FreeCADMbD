/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineIeqcJeqc.h"

namespace MbD {
    class DirectionCosineIeqctJeqc : public DirectionCosineIeqcJeqc
    {
        //pAijIeJept ppAijIeJepEIpt ppAijIeJepEJpt ppAijIeJeptpt 
    public:
        DirectionCosineIeqctJeqc();
        DirectionCosineIeqctJeqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineIeqcJeqc(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineIeqctJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
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

