/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistxyIecJec.h"

namespace MbD {
    class DistxyIeqcJec : public DistxyIecJec
    {
        //pdistxypXI pdistxypEI ppdistxypXIpXI ppdistxypXIpEI ppdistxypEIpEI

    public:
        DistxyIeqcJec() {}
        DistxyIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : DistxyIecJec(frmi, frmj) {}
        static std::shared_ptr<DistxyIeqcJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
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

