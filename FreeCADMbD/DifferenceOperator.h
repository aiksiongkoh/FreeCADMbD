/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>

#include "Numeric.h"
#include "FullMatrix.h"

namespace MbD {
    class DifferenceOperator : public Numeric
    {
        //iStep order taylorMatrix operatorMatrix time timeNodes 
    public:
        //virtual ~DifferenceOperator() {}
        virtual void initialize();
        
        void calcOperatorMatrix();
        virtual void initializeLocally();
        virtual void setiStep(size_t i);
        virtual void setorder(size_t o);
        virtual void formTaylorMatrix();
        virtual void instantiateTaylorMatrix();
        virtual void formTaylorRowwithTimeNodederivative(size_t i, size_t ii, size_t k);
        void settime(double t);
        void formDegenerateTaylorRow(size_t i) const;
        double currentStepSize() const;
        size_t direction() const;
        bool isConstantStepFor(size_t nsteps) const;
        bool isDecreasingStepFor(size_t nsteps) const;
        bool isIncreasingStepFor(size_t nsteps) const;
        FColDsptr valueWith(std::shared_ptr<std::vector<FColDsptr>> ypast);
        FColDsptr derivativewith(size_t deriv, std::shared_ptr<std::vector<FColDsptr>> series) const;
        virtual FColDsptr derivativeatpresentpast(size_t n, double t, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast);
        void noop();

        size_t iStep = 0, order = 0;
        FMatDsptr taylorMatrix, operatorMatrix;
        double time = 0.0;
        std::shared_ptr<std::vector<double>> timeNodes;    //"Row of past times in order of increasing past."
        static FRowDsptr OneOverFactorials;
    };
}

