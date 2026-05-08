/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIeqJeO.h"

namespace MbD {
    class OmeCompIeqJeqO : public OmeCompIeqJeO
    {
        void simUpdateAll() override;
    };
}
