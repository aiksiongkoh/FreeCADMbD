/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineIeqJe.h"

namespace MbD {
    class DirectionCosineIeqJeq : public DirectionCosineIeqJe
    {
        //pAijIeJepEJ ppAijIeJepEIpEJ ppAijIeJepEJpEJ pAjOJepEJT ppAjOJepEJpEJ 
    public:
        DirectionCosineIeqJeq();
        DirectionCosineIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineIeqJe(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEJ() override;

        FRowDsptr pAijIeJepEJ;
        FMatDsptr ppAijIeJepEIpEJ;
        FMatDsptr ppAijIeJepEJpEJ;
        FMatDsptr pAjOJepEJT;
        FMatFColDsptr ppAjOJepEJpEJ;

    };
}

