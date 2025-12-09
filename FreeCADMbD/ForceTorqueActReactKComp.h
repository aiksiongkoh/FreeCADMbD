/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueActReactComp.h"

namespace MbD {
    class ForceTorqueActReactKComp : public ForceTorqueActReactComp
    {
        //
    public:
        ForceTorqueActReactKComp() {}
        //ForceTorqueActReactKComp(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueActReactComp(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueActReactKComp> With();
        void initialize() override;
        static std::shared_ptr<ForceTorqueActReactKComp> ForceOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);
        static std::shared_ptr<ForceTorqueActReactKComp> TorqueOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);

        void calcPostDynCorrectorIteration() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void fillpFpydot(SpMatDsptr mat) override;
        void fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void forceOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);
        void torqueOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);

        FColDsptr aFTJeO;
    };
}
