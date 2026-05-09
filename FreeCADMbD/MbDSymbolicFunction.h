/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "CADSymbolicFunction.h"

namespace MbD {
    class KinematicIeJe;

    class MbDSymbolicFunction : public CADSymbolicFunction
    {
        //
    public:
        MbDSymbolicFunction(std::shared_ptr<Item> kineIJ) : mbdObject(kineIJ) {}
        static std::shared_ptr<MbDSymbolicFunction> With(std::shared_ptr<KinematicIeJe> kineIJ);
        void initialize() override;

        double getValue() override;
        Symsptr differentiateWRT(Symsptr var) override;
        void fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs) override;
        void fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs) override;
        void fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions) override;
        void fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions) override;
        void initializeGlobally();
        void initializeLocally();
        void postAccICIteration();
        void postCollisionCorrectorIteration();
        void postCollisionPredictor();
        void postDynCorrectorIteration();
        void postDynOutput();
        void postDynPredictor();
        void postInput();
        void postStaticIteration();
        void preAccIC();
        void preDynOutput();
        void preStatic();
        void useEquationNumbers();
        FRowDsptr pvaluepX(SpatialContainerFrame* partFrame);
        FRowDsptr pvaluepE(SpatialContainerFrame* partFrame);
        FRowDsptr pvaluepXdot(SpatialContainerFrame* partFrame);
        FRowDsptr pvaluepEdot(SpatialContainerFrame* partFrame);
        FRowDsptr pvaluepEI();
        FRowDsptr pvaluepXI();
        FRowDsptr pvaluepEJ();
        FRowDsptr pvaluepXJ();
        FRowDsptr pvaluepEK();
        FRowDsptr pvaluepXK();
        FRowDsptr pvaluepEdotI();
        FRowDsptr pvaluepXdotI();
        FRowDsptr pvaluepEdotJ();
        FRowDsptr pvaluepXdotJ();
        FRowDsptr pvaluepEdotK();
        FRowDsptr pvaluepXdotK();
        SpRowDsptr pvalueplam();
        SpatialContainerFrame* partFrameI();
        SpatialContainerFrame* partFrameJ();
        SpatialContainerFrame* partFrameK();

        std::shared_ptr<Item> mbdObject;
    };
}
