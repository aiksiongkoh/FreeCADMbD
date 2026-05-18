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

namespace MbD {
    class DistancexyConstraintIeJe : public ConstraintIeJe
    {
        //xIeJeIe yIeJeIe 
    public:
        DistancexyConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<DistancexyConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        virtual void init_xyIeJeIe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preStatic() override;
        void preVelIC() override;
        ConstraintType type() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        void postStaticIteration() override;

        std::shared_ptr<DispCompiIeJeIe> xIeJeIe, yIeJeIe;
        //ToDo: Use DistxyIeJe instead of xIeJeIe, yIeJeIe

    };
}

