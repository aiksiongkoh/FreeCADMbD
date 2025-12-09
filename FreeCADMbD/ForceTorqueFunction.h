/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "MbDSymbolicFunction.h"

namespace MbD {
    class ForceTorqueFunction : public ForceTorqueItem
    {
        //
    public:
        static std::shared_ptr<ForceTorqueFunction> With();
        void initialize() override;

        void calcPostDynCorrectorIteration() override;
        Symsptr getformula();
        void setformula(Symsptr function);
        double forTor();
        void initializeGlobally() override;
        void initializeLocally() override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postInput() override;
        void postStaticIteration() override;
        void preAccIC() override;
        void preDynOutput() override;
        void preStatic() override;
        void simUpdateAll() override;
        FColDsptr pFTpkineIJs();
        FColDsptr pFTpkinedotIJs();
        FColDsptr pFTpJtActs();

        std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs;
        std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs;
        std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions;
        Symsptr forTorFunc;
        std::shared_ptr<std::vector<Symsptr>> pFTpkineIJFuncs;
        std::shared_ptr<std::vector<Symsptr>> pFTpkinedotIJFuncs;
        std::shared_ptr<std::vector<Symsptr>> pFTpJtActFuncs;
    };
}
