/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "OrbitAngleZIecJec.h"

namespace MbD {
    class OrbitAngleZIeqcJec : public OrbitAngleZIecJec
    {
        //pthezpXI pthezpEI ppthezpXIpXI ppthezpXIpEI ppthezpEIpEI 
    public:
        OrbitAngleZIeqcJec();
        OrbitAngleZIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : OrbitAngleZIecJec(frmi, frmj) {}
        static std::shared_ptr<OrbitAngleZIeqcJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcppthezpEIpEI();
        void calcppthezpXIpEI();
        void calcppthezpXIpXI();
        void calcpthezpEI();
        void calcpthezpXI();
        void simUpdateAll() override;
        void init_xyIeJeIe() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepXIpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr pthezpXI, pthezpEI;
        FMatDsptr ppthezpXIpXI, ppthezpXIpEI, ppthezpEIpEI;
    };
}

