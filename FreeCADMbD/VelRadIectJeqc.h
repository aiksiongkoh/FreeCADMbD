/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIecJeqc.h"

namespace MbD {
    class VelRadIectJeqc : public VelRadIecJeqc
    {
        //
    public:
        VelRadIectJeqc() {}
        VelRadIectJeqc(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<VelRadIectJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);

    };
}

