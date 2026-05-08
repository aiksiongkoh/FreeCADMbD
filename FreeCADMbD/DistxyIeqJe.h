/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistxyIeJe.h"

namespace MbD {
    class DistxyIeqJe : public DistxyIeJe
    {
        //pdistxypXI pdistxypEI ppdistxypXIpXI ppdistxypXIpEI ppdistxypEIpEI

    public:
        DistxyIeqJe() {}
        DistxyIeqJe(EndFrmsptr frmi, EndFrmsptr frmj) : DistxyIeJe(frmi, frmj) {}
        static std::shared_ptr<DistxyIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcppdistxypEIpEI();
        void calcppdistxypXIpEI();
        void calcppdistxypXIpXI();
        void calcpdistxypEI();
        void calcpdistxypXI();
        void simUpdateAll() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepXIpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;

        FRowDsptr pdistxypXI, pdistxypEI;
        FMatDsptr ppdistxypXIpXI, ppdistxypXIpEI, ppdistxypEIpEI;
    };
}

