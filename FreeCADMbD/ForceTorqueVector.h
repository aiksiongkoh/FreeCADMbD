/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "ForceTorqueActReactComp.h"

namespace MbD {
    class ForceTorqueVector : public ForceTorqueItem
    {
        //components
    public:
        ForceTorqueVector() {}
        static std::shared_ptr<ForceTorqueVector> With();

        FColDsptr getFTIeO() const override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void functions(FColsptr<Symsptr> col);
        void initializeGlobally() override;
        void initializeLocally() override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postInput() override;
        void preAccIC() override;
        void preDynOutput() override;
        void preStatic() override;
        void simUpdateAll() override;
        void useEquationNumbers() override;

        std::shared_ptr<FullColumn<std::shared_ptr<ForceTorqueActReactComp>>> components;
    };
}
