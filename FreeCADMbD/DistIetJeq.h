/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DistIeJeq.h"

namespace MbD {
    class DistIetJeq : public DistIeJeq
    {
    public:
        DistIetJeq() {}
        DistIetJeq(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeJeq(frmi, frmj) {}
    };
}

