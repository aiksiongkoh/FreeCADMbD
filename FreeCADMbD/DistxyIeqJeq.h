/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistxyIeqJe.h"

namespace MbD {
    class DistxyIeqJeq : public DistxyIeqJe
    {
        //pdistxypXJ pdistxypEJ ppdistxypXIpXJ ppdistxypXIpEJ ppdistxypEIpXJ ppdistxypEIpEJ ppdistxypXJpXJ ppdistxypXJpEJ ppdistxypEJpEJ
    public:
        DistxyIeqJeq() {}
        DistxyIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistxyIeqJe(frmi, frmj) {}
        static std::shared_ptr<DistxyIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcppdistxypEIpEJ();
        void calcppdistxypEIpXJ();
        void calcppdistxypEJpEJ();
        void calcppdistxypXIpEJ();
        void calcppdistxypXIpXJ();
        void calcppdistxypXJpEJ();
        void calcppdistxypXJpXJ();
        void calcpdistxypEJ();
        void calcpdistxypXJ();
        void simUpdateAll() override;
        void init_xyIeJeIe() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FMatDsptr ppvaluepXIpEJ() override;
        FMatDsptr ppvaluepXIpXJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FMatDsptr ppvaluepXJpXJ() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepXJ() override;


        FRowDsptr pdistxypXJ, pdistxypEJ;
        FMatDsptr ppdistxypXIpXJ, ppdistxypXIpEJ, ppdistxypEIpXJ, ppdistxypEIpEJ, ppdistxypXJpXJ, ppdistxypXJpEJ, ppdistxypEJpEJ;

    };
}

