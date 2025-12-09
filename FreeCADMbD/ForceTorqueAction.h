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

namespace MbD {
    class ForceTorqueBasic;
    class ForceTorqueFunction;

    class ForceTorqueAction : public ForceTorqueItem
    {
        //
    public:
        ForceTorqueAction() {}
        ForceTorqueAction(size_t count);
        static std::shared_ptr<ForceTorqueAction> With(size_t count);
        void initialize() override;

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
        virtual void forceOnFrmIaxis(EndFrmsptr frmi, size_t axis);
        virtual void torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis);
        virtual void forceOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis);
        virtual void torqueOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis);

        std::shared_ptr<ForceTorqueBasic> forTorBasicI;
        std::shared_ptr<ForceTorqueFunction> forTorFunction;
    };
}
