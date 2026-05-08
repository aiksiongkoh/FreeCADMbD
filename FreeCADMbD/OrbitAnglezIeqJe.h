/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "OrbitAngleZIeJe.h"

namespace MbD {
    class OrbitAngleZIeqJe : public OrbitAngleZIeJe
    {
        //pthezpXI pthezpEI ppthezpXIpXI ppthezpXIpEI ppthezpEIpEI 
    public:
        OrbitAngleZIeqJe();
        OrbitAngleZIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : OrbitAngleZIeJe(frmi, frmj) {}
        static std::shared_ptr<OrbitAngleZIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcppthezpEIpEI();
        void calcppthezpXIpEI();
        void calcppthezpXIpXI();
        void calcpthezpEI();
        void calcpthezpXI();
        void simUpdateAll() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepXIpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr pthezpXI, pthezpEI;
        FMatDsptr ppthezpXIpXI, ppthezpXIpEI, ppthezpEIpEI;
    };
}

