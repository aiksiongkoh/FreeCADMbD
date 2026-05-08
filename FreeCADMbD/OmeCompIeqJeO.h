/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIeJeO.h"

namespace MbD {
    class OmeCompIeqJeO : public OmeCompIeJeO
    {
        void simUpdateAll() override;
    };
}
