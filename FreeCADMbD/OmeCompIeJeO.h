/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "KinematicDotIeJe.h"

namespace MbD {
    class OmeCompIeJeO : public KinematicDotIeJe
    {
    public:
        void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

        void simUpdateAll() override;
        size_t axis = SIZE_MAX;
    };
}
