/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"
#include "OrbitAngleZIeJe.h"

namespace MbD {
    class GearConstraintIJ : public ConstraintIeJe
    {
        //orbitIeJe orbitJeIe radiusI radiusJ 
    public:
        GearConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<GearConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        virtual void initorbitsIJ();
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        double ratio();
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;

        std::shared_ptr<OrbitAngleZIeJe> orbitIeJe, orbitJeIe;
        double radiusI = 0.0, radiusJ = 0.0;
    };
}

