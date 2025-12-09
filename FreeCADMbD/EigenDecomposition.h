/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "MatrixSolver.h"

namespace MbD {
    class EigenDecomposition : public MatrixSolver
    {

        //
    public:
        static std::shared_ptr<EigenDecomposition> With();

        FColDsptr basicSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal) override;
        FColDsptr basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal) override;
        void preSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal) override;
        void preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal) override;
        void doPivoting(size_t p) override;
        void forwardEliminateWithPivot(size_t p) override;
        void backSubstituteIntoDU() override;

        void postSolve() override;
        double getmatrixArowimaxMagnitude(size_t i) override;

    };
}

