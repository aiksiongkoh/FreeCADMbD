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
    class OmeCompIecJecKec : public KinematicDotIJ
    {
        //efrmK axisK omeiIeJeKe aAjOKe omeIeJeO 
    public:
        OmeCompIecJecKec() {}
        OmeCompIecJecKec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIJ(frmi, frmj) {}
        static std::shared_ptr<OmeCompIecJecKec> With();
        static std::shared_ptr<OmeCompIecJecKec> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis) override;

        double value() override;
        void calcPostDynCorrectorIteration() override;

        EndFrmsptr efrmK;
        size_t axisK;
        double omeiIeJeKe;
        FColDsptr aAjOKe;
        FColDsptr omeIeJeO;
    };
}
