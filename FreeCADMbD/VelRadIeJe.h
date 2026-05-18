/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicDotIeJe.h"
#include "DispIeJeO.h"

namespace MbD {
    class VelRadIeJe : public KinematicDotIeJe
    {
        //rIeJe rIeJeO uIeJeO vIeJe vIeJeO 
    public:
        VelRadIeJe() {}
        VelRadIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIeJe(frmi, frmj) {}
        static std::shared_ptr<VelRadIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void initialize() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        void simUpdateAll() override;
        double value() override;

        std::shared_ptr<DispIeJeO> dispIeJeO; 
        double rIeJe = 0.0, vIeJe = 0.0;
        FColDsptr rIeJeO;
        FColDsptr uIeJeO;
        FColDsptr vIeJeO;

    };
}

