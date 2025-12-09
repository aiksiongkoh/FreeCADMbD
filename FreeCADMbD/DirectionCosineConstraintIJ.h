/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIJ.h"

namespace MbD {
    class DirectionCosineIecJec;

    class DirectionCosineConstraintIJ : public ConstraintIJ
    {
        //axisI axisJ aAijIeJe 
    public:
        DirectionCosineConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : ConstraintIJ(frmi, frmj), axisI(axisi), axisJ(axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        virtual void initaAijIeJe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        void simUpdateAll() override;
        ConstraintType type() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;

        size_t axisI, axisJ;
        std::shared_ptr<DirectionCosineIecJec> aAijIeJe;
    };
}

