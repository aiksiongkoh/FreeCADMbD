/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicDotIJ.h"
#include "DispIeJeO.h"

namespace MbD {
    class VelRadIecJec : public KinematicDotIJ
    {
        //rIeJe rIeJeO uIeJeO vIeJe vIeJeO 
    public:
        VelRadIecJec() {}
        VelRadIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIJ(frmi, frmj) {}
        static std::shared_ptr<VelRadIecJec> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        double value() override;

        std::shared_ptr<DispIeJeO> dispIeJeO; 
        double rIeJe = 0.0, vIeJe = 0.0;
        FColDsptr rIeJeO, uIeJeO, vIeJeO;

    };
}

