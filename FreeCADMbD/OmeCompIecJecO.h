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
    class OmeCompIecJecO : public KinematicDotIJ
    {
    public:
        void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

        size_t axis = SIZE_MAX;
    };
}
