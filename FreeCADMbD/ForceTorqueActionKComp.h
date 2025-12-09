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
    class ForceTorqueActionKComp : public ForceTorqueActionComp
    {
        //
    public:
        static std::shared_ptr<ForceTorqueActionKComp> With();
        
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
        FColDsptr getFTIeO() const override;
        void forceOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis);
        void torqueOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis);

        PartFrame* pfrmK;
        FColDsptr aFTIeO;
        EndFrmsptr efrmK;
        FColDsptr aAjOKe;


        ForceTorqueActionKComp() = default;
    };
}
