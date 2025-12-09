/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueBasic.h"
#include "Part.h"

namespace MbD {
    class ForceBasicqcVector : public ForceTorqueBasic
    {
        //iqX prOeOpET 
    public:
        static std::shared_ptr<ForceBasicqcVector> With();

        void calcPostDynCorrectorIteration();
        void fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO) override;
        void fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam) override;
        void fillDynErroraFTO(FColDsptr col, FColDsptr aFTO) override;
        void fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO) override;
        void fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj) override;
        void fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj) override;
        void fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj) override;
        void fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj) override;
        void fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot) override;
        void fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj) override;
        void fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj) override;
        void useEquationNumbers() override;

        size_t iqX;
        FMatDsptr prOeOpET;
    };
}

