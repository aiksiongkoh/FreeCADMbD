/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "VelRadIeqcJeqc.h"

namespace MbD {
    class VelRadIeqctJeqc : public VelRadIeqcJeqc
    {
        //
    public:
        VelRadIeqctJeqc() {}
		VelRadIeqctJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqcJeqc(frmi, frmj) {}
        static std::shared_ptr<VelRadIeqctJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);

    };
}

