/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispCompIecJeqcO.h"

namespace MbD {
    class DispCompIectJeqcO : public DispCompIecJeqcO
    {
        //priIeJeOpt ppriIeJeOpEJpt ppriIeJeOptpt 
    public:
        DispCompIectJeqcO() {}
        DispCompIectJeqcO(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : DispCompIecJeqcO(frmi, frmj, axisO) {}
        static std::shared_ptr<DispCompIectJeqcO> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);

        double ppvalueptpt() override;
        void preAccIC() override;
        void preVelIC() override;
        double pvaluept() override;

        double priIeJeOpt;
        double ppriIeJeOptpt;
    };
}

