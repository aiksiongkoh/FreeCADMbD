/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueActionComp.h"

namespace MbD {
    class ForceTorqueActionOComp : public ForceTorqueActionComp
    {
        //
    public:
        static std::shared_ptr<ForceTorqueActionOComp> With();
        
        void calcPostDynCorrectorIteration() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void fillpFpydot(SpMatDsptr mat) override;
        void fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
        void torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
        void forceOnFrmIaxis(EndFrmsptr frmi, size_t axis);
        void torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis);
        FColDsptr getFTIeO() const override;
        void postDynPredictor() override;

        double aFTIeOi;
    };
}
