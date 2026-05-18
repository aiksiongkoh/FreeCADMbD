/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicIeJe.h"

namespace MbD {
    class KinematicDotIeJe : public KinematicIeJe
    {
        //
    public:
        KinematicDotIeJe() {}
        KinematicDotIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIeJe(frmi, frmj) {}
        static std::shared_ptr<KinematicDotIeJe> With();
        static std::shared_ptr<KinematicDotIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void postStaticIteration() override;
        bool isKineIJ() override;
        bool isKinedotIJ() override;
        virtual FRowDsptr pvaluepXdot(SpatialContainerFrame* partFrame);
        virtual FRowDsptr pvaluepEdot(SpatialContainerFrame* partFrame);
        virtual FRowDsptr pvaluepEdotI();
        virtual FRowDsptr pvaluepEdotJ();
        virtual FRowDsptr pvaluepEdotK();
        virtual FRowDsptr pvaluepXdotI();
        virtual FRowDsptr pvaluepXdotJ();
        virtual FRowDsptr pvaluepXdotK();

    };
}

