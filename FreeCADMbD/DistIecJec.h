/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIJ.h"

namespace MbD {
    class DistIecJec : public KinematicIJ
    {
        //rIeJe rIeJeO uIeJeO muIeJeO 
    public:
        DistIecJec() {}
        DistIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<DistIecJec> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcPostDynCorrectorIteration() override;
        virtual void calcPrivate();
        double value() override;
        FColDsptr rIeJeIe();
        virtual FMatDsptr puIeJeOpX(SpatialContainerFrame* partFrame);
        virtual FMatDsptr puIeJeOpE(SpatialContainerFrame* partFrame);
        FMatDsptr puIeJeOpEI() override;
        FMatDsptr puIeJeOpXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXI() override;

        double rIeJe = 0.0;
        FColDsptr rIeJeO, uIeJeO, muIeJeO;
    };
}

