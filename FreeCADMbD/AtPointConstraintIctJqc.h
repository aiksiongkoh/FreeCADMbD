/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AtPointConstraintIcJqc.h"

namespace MbD {
    class AtPointConstraintIctJqc : public AtPointConstraintIcJqc
    {
        //pGpt ppGpEIpt ppGptpt 
    public:
        AtPointConstraintIctJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIcJqc(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIctJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void initializeGlobally() override;
        void initriIeJeO() override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = 0.0;
        double ppGptpt = 0.0;

    };
}

