/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIeJe.h"
#include "DirectionCosineIeqJe.h"

namespace MbD {
    class AngleZIeJe : public KinematicIeJe
    {
        //thez aA00IeJe aA10IeJe cosOverSSq sinOverSSq twoCosSinOverSSqSq dSqOverSSqSq 
    public:
        AngleZIeJe() {}
        AngleZIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIeJe(frmi, frmj) {}
        static std::shared_ptr<AngleZIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        virtual void init_aAijIeJe();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        double value() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;

        double thez = std::numeric_limits<double>::min();
        double cosOverSSq = 0.0, sinOverSSq = 0.0, twoCosSinOverSSqSq = 0.0, dSqOverSSqSq = 0.0;
        std::shared_ptr<DirectionCosineIeJe> aA00IeJe, aA10IeJe;
    };
}

