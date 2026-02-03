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
    class KinematicDotIJ : public KinematicIJ
    {
        //
    public:
        KinematicDotIJ() {}
        KinematicDotIJ(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<KinematicDotIJ> With();
        static std::shared_ptr<KinematicDotIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
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

