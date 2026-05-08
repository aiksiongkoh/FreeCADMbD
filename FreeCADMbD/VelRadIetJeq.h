/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeJeq.h"

namespace MbD {
    class VelRadIetJeq : public VelRadIeJeq
    {
        //
    public:
        VelRadIetJeq() {}
        VelRadIetJeq(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<VelRadIetJeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

    };
}

