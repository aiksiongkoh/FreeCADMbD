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
    class DispCompIecJecIe : public KinematicIJ
    {
        //axis riIeJeIe aAjOIe rIeJeO 
    public:
        DispCompIecJecIe() : axis(0), riIeJeIe(0.0) {}
        DispCompIecJecIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
            : KinematicIJ(frmi, frmj), axis(axis), riIeJeIe(0.0) {}
        static std::shared_ptr<DispCompIecJecIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

        void calc_value() override;
        void calcPostDynCorrectorIteration() override;
        double value() override;

        size_t axis = SIZE_MAX;
        double riIeJeIe = 0.0;
        FColDsptr aAjOIe, rIeJeO;
    };
}

