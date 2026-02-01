/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistIeqcJeqc.h"

namespace MbD {
    class DistIeqctJeqc : public DistIeqcJeqc
    {
        //prIeJept pprIeJepXIpt pprIeJepEIpt pprIeJepXJpt pprIeJepEJpt pprIeJeptpt 
    public:
        DistIeqctJeqc() {}
        DistIeqctJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistIeqcJeqc(frmi, frmj) {}
        static std::shared_ptr<DistIeqctJeqc> With();
        static std::shared_ptr<DistIeqctJeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        double prIeJept = 0.0;
        FRowDsptr pprIeJepXIpt;
        FRowDsptr pprIeJepEIpt;
        FRowDsptr pprIeJepXJpt;
        FRowDsptr pprIeJepEJpt;
        double pprIeJeptpt = 0.0;

    };
}

