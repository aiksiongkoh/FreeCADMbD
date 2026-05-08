/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeqJeq.h"

namespace MbD {
    class VelRadIeqtJeq : public VelRadIeqJeq
    {
        //
    public:
        VelRadIeqtJeq() {}
        VelRadIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqJeq(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

    };
}

