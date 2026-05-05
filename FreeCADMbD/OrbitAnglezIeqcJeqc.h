/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "OrbitAngleZIeqcJec.h"

namespace MbD {
    class OrbitAngleZIeqcJeqc : public OrbitAngleZIeqcJec
    {
        //pthezpXJ pthezpEJ ppthezpXIpXJ ppthezpXIpEJ ppthezpEIpXJ ppthezpEIpEJ ppthezpXJpXJ ppthezpXJpEJ ppthezpEJpEJ 
    public:
        OrbitAngleZIeqcJeqc();
        OrbitAngleZIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OrbitAngleZIeqcJec(frmi, frmj) {}
        static std::shared_ptr<OrbitAngleZIeqcJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
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

