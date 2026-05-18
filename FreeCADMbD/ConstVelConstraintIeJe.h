/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"

namespace MbD {
    class DirectionCosineIeJe;

    class ConstVelConstraintIeJe : public ConstraintIeJe
    {
        //aA01IeJe aA10IeJe 
    public:
        ConstVelConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<ConstVelConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        virtual void initA01IeJe();
        virtual void initA10IeJe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preStatic() override;
        void preVelIC() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        void addToJointForceI(FColDsptr col);
        void addToJointTorqueI(FColDsptr col) override;
        void postStaticIteration() override;

        std::shared_ptr<DirectionCosineIeJe> aA01IeJe, aA10IeJe;
    };
}

