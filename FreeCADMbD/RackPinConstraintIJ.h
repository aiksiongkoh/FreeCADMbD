/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIJ.h"
#include "DispCompIecJecIe.h"
#include "AngleZIecJec.h"

namespace MbD {
    class RackPinConstraintIJ : public ConstraintIJ
    {
        //xIeJeIe thezIeJe pitchRadius 
    public:
        RackPinConstraintIJ() : pitchRadius(0.0) {}
        RackPinConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIJ(frmi, frmj), pitchRadius(0.0) {}
        static std::shared_ptr<RackPinConstraintIJ> With();
        static std::shared_ptr<RackPinConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        virtual void initxIeJeIe();
        virtual void initthezIeJe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        void simUpdateAll() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        std::string constraintSpec() override;

        std::shared_ptr<DispCompIecJecIe> xIeJeIe;
        std::shared_ptr<AngleZIecJec> thezIeJe;
        double pitchRadius = 0.0;
    };
}

