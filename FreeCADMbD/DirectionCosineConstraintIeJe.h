/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"
#include "DirectionCosineIeJe.h"

namespace MbD {
    class DirectionCosineConstraintIeJe : public ConstraintIeJe
    {
    public:
        DirectionCosineConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : axisI(axisi), axisJ(axisj), ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<DirectionCosineConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);


        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void simUpdateAll() override;

        void postInput() override;

        void prePosIC() override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void postPosICIteration() override;

        void preVelIC() override;
        void fillVelICJacob(SpMatDsptr mat) override;

        void preAccIC() override;
        void fillAccICIterError(FColDsptr col) override;

        void preDyn() override;
        void preDynOutput() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration();
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointForceJ(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void addToJointTorqueJ(FColDsptr col) override;
        void calcG() override;
        ConstraintType type() override;
        std::string constraintSpec() override;
        virtual void initaAijIeJe() = 0;



        size_t axisI = SIZE_MAX, axisJ = SIZE_MAX;
        std::shared_ptr<DirectionCosineIeJe> aAijIeJe;

    };
}

