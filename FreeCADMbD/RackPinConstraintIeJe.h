/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ConstraintIeJe.h"
#include "DispCompiIeJeIe.h"
#include "AngleZIeJe.h"

namespace MbD {
    class RackPinConstraintIeJe : public ConstraintIeJe
    {
        //xIeJeIe thezIeJe pitchRadius 
    public:
        RackPinConstraintIeJe() {}
        RackPinConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<RackPinConstraintIeJe> With();
        static std::shared_ptr<RackPinConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        virtual void initxIeJeIe();
        virtual void initthezIeJe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        std::string constraintSpec() override;

        std::shared_ptr<DispCompiIeJeIe> xIeJeIe;
        std::shared_ptr<AngleZIeJe> thezIeJe;
        double pitchRadius = 0.0;
    };
}

