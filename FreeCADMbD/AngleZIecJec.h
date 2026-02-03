/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIJ.h"
#include "DirectionCosineIeqcJec.h"

namespace MbD {
    class AngleZIecJec : public KinematicIJ
    {
        //thez aA00IeJe aA10IeJe cosOverSSq sinOverSSq twoCosSinOverSSqSq dSqOverSSqSq 
    public:
        AngleZIecJec() {}
        AngleZIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
        static std::shared_ptr<AngleZIecJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
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
        std::shared_ptr<DirectionCosineIecJec> aA00IeJe, aA10IeJe;
    };
}

