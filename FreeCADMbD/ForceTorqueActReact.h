/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "ForceTorqueAction.h"
#include "ForceTorqueBasic.h"

namespace MbD {
    class ForceTorqueActReact : public ForceTorqueItem
    {
        //
    public:
        ForceTorqueActReact() {}
        //ForceTorqueActReact(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueItem(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueActReact> With();
        
        FColDsptr getFTIeO() const override;
        std::shared_ptr<ForceTorqueFunction> getforTorFunction();
        void setforTorFunction(std::shared_ptr<ForceTorqueFunction> forTorFunction);
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
        void useEquationNumbers() override;

        std::shared_ptr<ForceTorqueAction> forTorAction;
        std::shared_ptr<ForceTorqueBasic> forTorBasicJ;
    };
}
