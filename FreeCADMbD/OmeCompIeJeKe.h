/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include <cassert>
#include "KinematicDotIeJe.h"

namespace MbD {
    class OmeCompIeJeKe : public KinematicDotIeJe
    {
    public:
        OmeCompIeJeKe() {}
        OmeCompIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : KinematicDotIeJe(frmi, frmj), eFrmK(frmk), axisK(axisk) { assert(eFrmI == eFrmK); }
        static std::shared_ptr<OmeCompIeJeKe> With();
        static std::shared_ptr<OmeCompIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);

        double value() override;
        void simUpdateAll() override;

        EndFrmsptr eFrmK;
        size_t axisK = SIZE_MAX;
        double omeiIeJeKe = 0.0;
        FColDsptr aAjOKe;
        FColDsptr omeIeJeO;
    };
}
