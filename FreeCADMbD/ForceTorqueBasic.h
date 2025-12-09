/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "MarkerFrame.h"
#include "Part.h"

namespace MbD {
    class EndFrameqc;

    class ForceTorqueBasic : public ForceTorqueItem
    {
        //
    public:
        static std::shared_ptr<ForceTorqueBasic> With();
        
        virtual void fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO);
        virtual void fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam);
        virtual void fillDynErroraFTO(FColDsptr col, FColDsptr aFTO);
        virtual void fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO);
        virtual void fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj);
        virtual void fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj);
        virtual void fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj);
        virtual void fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj);
        virtual void fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot);
        virtual void fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj);
        virtual void fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj);
        void useEquationNumbers() override;
        virtual void fillAccICIterErroraFTOi(FColDsptr col, double aFTOi);
        virtual void fillpFpydotpFOpmudot(SpMatDsptr mat, SpMatDsptr pFOpmudot);
        virtual void endFramefollowEndFrame(EndFrmsptr frmj, EndFrmsptr frmi);

        ForceTorqueItem* parent;   //Use pointer to point backwards.
        EndFrmsptr endFrame;
        size_t iqE;
    };
}
