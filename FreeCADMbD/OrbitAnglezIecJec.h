/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIJ.h"
#include "DispCompIecJecIe.h"

namespace MbD {
    class OrbitAngleZIecJec : public KinematicIJ
    {
        //thez xIeJeIe yIeJeIe cosOverSSq sinOverSSq twoCosSinOverSSqSq dSqOverSSqSq 
    public:
        OrbitAngleZIecJec() {};
        OrbitAngleZIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<OrbitAngleZIecJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        virtual void init_xyIeJeIe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        void simUpdateAll() override;
        double value() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;

        double thez = std::numeric_limits<double>::min();
        double cosOverSSq = 0.0, sinOverSSq = 0.0, twoCosSinOverSSqSq = 0.0, dSqOverSSqSq = 0.0;
        std::shared_ptr<DispCompIecJecIe> xIeJeIe, yIeJeIe;
    };
}

