/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueActReact.h"
#include "MarkerFrame.h"

namespace MbD {
    class ForceTorqueActReactInLine : public ForceTorqueActReact
    {
        //
    public:
        static std::shared_ptr<ForceTorqueActReactInLine> With();
        void initialize() override;
        static std::shared_ptr<ForceTorqueActReactInLine> ForceOnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<ForceTorqueActReactInLine> TorqueOnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcPostDynCorrectorIteration() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void fillpFpydot(SpMatDsptr mat) override;
        void fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function);
        void forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postInput() override;
        void postStaticIteration() override;
        void preAccIC() override;
        void preDynOutput() override;
        void preStatic() override;
        void simUpdateAll() override;
        void torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;

        FColDsptr aFTJeO;

    };
}
