/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "SystemNewtonRaphson.h"

namespace MbD {
    class StaticICNewtonRaphson : public SystemNewtonRaphson
    {
        //Static initial conditions.
    public:
        static std::shared_ptr<StaticICNewtonRaphson> With();

        void askSystemToUpdate() override;
        void assignEquationNumbers() override;
        void createVectorsAndMatrices() override;
        void fillPyPx() override;
        void fillY() override;
        void incrementIterNo() override;
        void initializeGlobally() override;
        void logSingularMatrixMessage();
        void passRootToSystem() override;
        void postRun() override;
        void preRun() override;

        size_t nqsu = SIZE_MAX;
        FColDsptr qsuOld;
        DiagMatDsptr qsuWeights;
    };
}

