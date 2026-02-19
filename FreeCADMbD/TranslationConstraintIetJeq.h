/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "TranslationConstraintIeJeq.h"

namespace MbD {
    class TranslationConstraintIetJeq : public TranslationConstraintIeJeq
    {
        //pGpt ppGpXIpt ppGpEIpt ppGpXJpt ppGpEJpt ppGptpt 
    public:
        TranslationConstraintIetJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIeJeq(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIetJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void initriIeJeIe() override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = 0.0;
        FRowDsptr ppGpXJpt;
        FRowDsptr ppGpEJpt;
        double ppGptpt = 0.0;
    };
}

