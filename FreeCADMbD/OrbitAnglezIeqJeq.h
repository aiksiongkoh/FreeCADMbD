/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "OrbitAngleZIeqJe.h"

namespace MbD {
    class OrbitAngleZIeqJeq : public OrbitAngleZIeqJe
    {
        //pthezpXJ pthezpEJ ppthezpXIpXJ ppthezpXIpEJ ppthezpEIpXJ ppthezpEIpEJ ppthezpXJpXJ ppthezpXJpEJ ppthezpEJpEJ 
    public:
        OrbitAngleZIeqJeq();
        OrbitAngleZIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : OrbitAngleZIeqJe(frmi, frmj) {}
        static std::shared_ptr<OrbitAngleZIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;
        void init_xyIeJeIe() override;

        void calcppthezpEIpEJ();
        void calcppthezpEIpXJ();
        void calcppthezpEJpEJ();
        void calcppthezpXIpEJ();
        void calcppthezpXIpXJ();
        void calcppthezpXJpEJ();
        void calcppthezpXJpXJ();
        void calcpthezpEJ();
        void calcpthezpXJ();
        void simUpdateAll() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FMatDsptr ppvaluepXIpEJ() override;
        FMatDsptr ppvaluepXIpXJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FMatDsptr ppvaluepXJpXJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;


        FRowDsptr pthezpXJ, pthezpEJ;
        FMatDsptr ppthezpXIpXJ, ppthezpXIpEJ, ppthezpEIpXJ, ppthezpEIpEJ, ppthezpXJpXJ, ppthezpXJpEJ, ppthezpEJpEJ;
    };
}

