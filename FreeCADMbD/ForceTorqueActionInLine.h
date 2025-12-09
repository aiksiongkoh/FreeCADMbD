/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueAction.h"
#include "DistIeqcJeqc.h"

namespace MbD {
    class ForceTorqueActionInLine : public ForceTorqueAction
    {
        //
    public:
        static std::shared_ptr<ForceTorqueActionInLine> With();
        void initialize() override;

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
        std::shared_ptr<ForceTorqueFunction> tension();
        void torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
        FColDsptr uIeJeO();
        void useEquationNumbers() override;
        FColDsptr getFTIeO() const override;

        std::shared_ptr<DistIeqcJeqc> distIeJe;
        FColDsptr aFTIeO;
    };
}
