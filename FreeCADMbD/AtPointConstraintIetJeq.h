/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AtPointConstraintIeJeq.h"

namespace MbD {
    class AtPointConstraintIetJeq : public AtPointConstraintIeJeq
    {
        //pGpt ppGpEIpt ppGptpt 
    public:
        AtPointConstraintIetJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIeJeq(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIetJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void initializeGlobally() override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = std::numeric_limits<double>::min();
        //ppGpEIpt = 0 row vector
        double ppGptpt = std::numeric_limits<double>::min();

    };
}

