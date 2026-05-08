/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineIeJe.h"

namespace MbD {
    class DirectionCosineIeqJe : public DirectionCosineIeJe
    {
        //pAijIeJepEI ppAijIeJepEIpEI pAjOIepEIT ppAjOIepEIpEI 
    public:
        DirectionCosineIeqJe();
        DirectionCosineIeqJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineIeJe(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;

        void simUpdateAll() override;
        void initializeGlobally() override;
        FMatDsptr ppvaluepEIpEI() override;
        FRowDsptr pvaluepEI() override;

        FRowDsptr pAijIeJepEI;
        FMatDsptr ppAijIeJepEIpEI;
        FMatDsptr pAjOIepEIT;
        FMatFColDsptr ppAjOIepEIpEI;
    };
}

