/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AtPointConstraintIeqJeq.h"

namespace MbD {
    class AtPointConstraintIeqtJeq : public AtPointConstraintIeqJeq
    {
        //pGpt ppGpEIpt ppGptpt 
    public:
        AtPointConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIeqJeq(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void initializeGlobally() override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = std::numeric_limits<double>::min();
        FRowDsptr ppGpEIpt;
        double ppGptpt = std::numeric_limits<double>::min();

    };
}

