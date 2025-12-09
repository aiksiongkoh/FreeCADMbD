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
    class DispCompIecJecO : public KinematicIJ
    {
        //axis riIeJeO 
    public:
        DispCompIecJecO() {}
        DispCompIecJecO(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : KinematicIJ(frmi, frmj), axis(axisO) {}
        static std::shared_ptr<DispCompIecJecO> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

        void calcPostDynCorrectorIteration() override;
        double value() override;

        size_t axis = SIZE_MAX;
        double riIeJeO = 0.0;
    };
}

