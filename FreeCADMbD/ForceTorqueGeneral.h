/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueIJ.h"
#include "ForceVector.h"
#include "TorqueVector.h"

namespace MbD {
    class ForceTorqueGeneral : public ForceTorqueIJ
    {
        //forceVector torqueVector 
    public:
        ForceTorqueGeneral() {}
        static std::shared_ptr<ForceTorqueGeneral> OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<ForceTorqueGeneral> OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

        void onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
        FColDsptr aFX() const override;
        FColDsptr aTX() const override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void fillStaticError(FColDsptr col) override;
        void fillStaticJacob(SpMatDsptr mat) override;
        void forceFunctions(FColsptr<Symsptr> col);
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
        void torqueFunctions(FColsptr<Symsptr> col);
        void useEquationNumbers() override;

        std::shared_ptr<ForceVector> forceVector;
        std::shared_ptr<TorqueVector> torqueVector;
    };
}

