/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "TranslationConstraintIeqJeq.h"

namespace MbD {
    class TranslationConstraintIeqtJeq : public TranslationConstraintIeqJeq
    {
        //pGpt ppGpXIpt ppGpEIpt ppGpXJpt ppGpEJpt ppGptpt 
    public:
        TranslationConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIeqJeq(frmi, frmj, axisi) {}
        static std::shared_ptr<TranslationConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

        void fillAccICIterError(FColDsptr col) override;
        void fillVelICError(FColDsptr col) override;
        void preAccIC() override;
        void preVelIC() override;
        ConstraintType type() override;

        double pGpt = 0.0;
        FRowDsptr ppGpXIpt;
        FRowDsptr ppGpEIpt;
        FRowDsptr ppGpXJpt;
        FRowDsptr ppGpEJpt;
        double ppGptpt = 0.0;
    };
}

