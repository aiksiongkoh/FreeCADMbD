/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "KinematicDotIJ.h"

namespace MbD {
    class OmeCompIeJeKe : public KinematicDotIJ
    {
        //efrmK axisK omeiIeJeKe aAjOKe omeIeJeO 
    public:
        OmeCompIeJeKe() {}
        OmeCompIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIJ(frmi, frmj) {}
        OmeCompIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : KinematicDotIJ(frmi, frmj), efrmK(efrmK), axisK(axisK) {}
        static std::shared_ptr<OmeCompIeJeKe> With();
        static std::shared_ptr<OmeCompIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis) override;

        double value() override;
        void simUpdateAll() override;

        EndFrmsptr efrmK;
        size_t axisK = SIZE_MAX;
        double omeiIeJeKe = 0.0;
        FColDsptr aAjOKe;
        FColDsptr omeIeJeO;
    };
}
