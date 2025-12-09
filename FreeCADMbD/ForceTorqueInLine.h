/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueIJ.h"
#include "MarkerFrame.h"
#include "ForceTorqueActReactInLine.h"

namespace MbD {
    class ForceTorqueInLine : public ForceTorqueIJ
    {
        //
    public:
        ForceTorqueInLine(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueIJ(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueInLine> With(EndFrmsptr frmi, EndFrmsptr frmj);

        FColDsptr aFX() const override;
        FColDsptr aTX() const override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void fillStaticError(FColDsptr col) override;
        void fillStaticJacob(SpMatDsptr mat) override;
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
        void tension(Symsptr tensionFunc);
        void twist(Symsptr twistFunc);
        void useEquationNumbers() override;

        std::shared_ptr<ForceTorqueActReactInLine> forceInLine, torqueInLine;
    };
}
