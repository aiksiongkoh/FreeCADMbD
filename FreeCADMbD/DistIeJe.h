/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicIJ.h"
#include "DispIeJeO.h"

namespace MbD {
    class DistIeJe : public KinematicIJ
    {
    public:
        DistIeJe() {}
        DistIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<DistIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        virtual void calcPrivate();
        double value() override;
        virtual FMatDsptr puIeJeOpX(SpatialContainerFrame* partFrame);
        virtual FMatDsptr puIeJeOpE(SpatialContainerFrame* partFrame);
        FMatDsptr puIeJeOpEI() override;
        FMatDsptr puIeJeOpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;
        
        // dispIeJeO is updated at global level
        std::shared_ptr<DispIeJeO> dispIeJeO; 
        double rIeJe = std::numeric_limits<double>::min();
        FColDsptr rIeJeO, uIeJeO, muIeJeO;
    };
}

